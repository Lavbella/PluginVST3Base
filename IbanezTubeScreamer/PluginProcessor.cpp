#include "PluginProcessor.h"
#include "PluginEditor.h"

IbanezTubeScreamerAudioProcessor::IbanezTubeScreamerAudioProcessor()
    : AudioProcessor (BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                       .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "Parameters", createParameterLayout())
{
}

IbanezTubeScreamerAudioProcessor::~IbanezTubeScreamerAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout IbanezTubeScreamerAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"drive", 1}, "Drive", 1.0f, 20.0f, 5.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"tone", 1}, "Tone", 0.0f, 1.0f, 0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"level", 1}, "Level", 0.0f, 1.0f, 0.7f));

    return { params.begin(), params.end() };
}

void IbanezTubeScreamerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    inputHighPass.prepare(spec);
    toneLowPass.prepare(spec);
    
    *inputHighPass.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 720.0f);
}

void IbanezTubeScreamerAudioProcessor::releaseResources() {}

void IbanezTubeScreamerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Leitura dos parâmetros do APVTS
    float driveParam = apvts.getRawParameterValue("drive")->load();
    float toneParam = apvts.getRawParameterValue("tone")->load();
    float levelParam = apvts.getRawParameterValue("level")->load();

    // Atualização dinâmica do filtro Tone
    float toneFreq = 1000.0f + (toneParam * 3000.0f);
    *toneLowPass.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), toneFreq);

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    // Corte de graves (Filtro passa-alto de entrada)
    inputHighPass.process(context);

    // Processamento da distorção clássica do TS
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float inputSample = channelData[sample];
            float drivenSample = inputSample * driveParam;
            float distortedSample = 0.0f;

            // Saturação simétrica suave (Soft Clipping)
            if (drivenSample > 1.0f)         distortedSample = 2.3f / 3.0f;
            else if (drivenSample < -1.0f)   distortedSample = -2.3f / 3.0f;
            else                             distortedSample = drivenSample - ((drivenSample * drivenSample * drivenSample) / 3.0f);

            float blendedSample = (distortedSample * 0.7f) + (inputSample * 0.3f);
            channelData[sample] = blendedSample * levelParam;
        }
    }

    // Filtro passa-baixo de saída para moldar agudos
    toneLowPass.process(context);
}

juce::AudioProcessorEditor* IbanezTubeScreamerAudioProcessor::createEditor() 
{ 
    return new IbanezTubeScreamerAudioProcessorEditor (*this); 
}

void IbanezTubeScreamerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void IbanezTubeScreamerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr && xmlState->hasTagName (apvts.state.getType()))
        apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

// ==============================================================================
// Esta é a função que o JUCE procura e que estava em falta ou desatualizada:
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IbanezTubeScreamerAudioProcessor();
}