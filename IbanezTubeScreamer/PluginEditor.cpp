#include "PluginProcessor.h"
#include "PluginEditor.h"

IbanezTubeScreamerAudioProcessorEditor::IbanezTubeScreamerAudioProcessorEditor (IbanezTubeScreamerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (450, 250);

    auto setupSlider = [this](juce::Slider& slider, juce::Label& label, const juce::String& name) {
        slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (slider);

        label.setText (name, juce::dontSendNotification);
        label.setJustificationType (juce::Justification::centred);
        label.setFont (juce::FontOptions (14.0f, juce::Font::bold));
        label.setColour (juce::Label::textColourId, juce::Colours::white);
        addAndMakeVisible (label);
    };

    setupSlider (driveSlider, driveLabel, "DRIVE");
    setupSlider (toneSlider, toneLabel, "TONE");
    setupSlider (levelSlider, levelLabel, "LEVEL");

    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "drive", driveSlider);
    toneAttachment  = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "tone", toneSlider);
    levelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "level", levelSlider);
}

IbanezTubeScreamerAudioProcessorEditor::~IbanezTubeScreamerAudioProcessorEditor() {}

void IbanezTubeScreamerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Verde clássico do TS9
    g.fillAll (juce::Colour::fromRGB (116, 179, 74));

    // Texto de estilo do pedal
    g.setColour (juce::Colours::black.withAlpha (0.4f));
    g.setFont (juce::FontOptions (24.0f, juce::Font::bold));
    g.drawText ("TS-9 CLONE", getLocalBounds().removeFromBottom(40), juce::Justification::centred, true);
}

void IbanezTubeScreamerAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (20);
    auto width = area.getWidth() / 3;

    // Define posições lado a lado de forma dinâmica
    auto driveArea = area.removeFromLeft (width);
    driveLabel.setBounds (driveArea.removeFromTop (20));
    driveSlider.setBounds (driveArea);

    auto toneArea = area.removeFromLeft (width);
    toneLabel.setBounds (toneArea.removeFromTop (20));
    toneSlider.setBounds (toneArea);

    auto levelArea = area;
    levelLabel.setBounds (levelArea.removeFromTop (20));
    levelSlider.setBounds (levelArea);
}