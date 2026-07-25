#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

class IbanezTubeScreamerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    IbanezTubeScreamerAudioProcessorEditor (IbanezTubeScreamerAudioProcessor&);
    ~IbanezTubeScreamerAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    IbanezTubeScreamerAudioProcessor& audioProcessor;

    juce::Slider driveSlider;
    juce::Slider toneSlider;
    juce::Slider levelSlider;

    juce::Label driveLabel;
    juce::Label toneLabel;
    juce::Label levelLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> toneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> levelAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IbanezTubeScreamerAudioProcessorEditor)
};
