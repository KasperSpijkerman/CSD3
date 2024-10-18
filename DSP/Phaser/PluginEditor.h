#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class PhaserAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    PhaserAudioProcessorEditor (PhaserAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~PhaserAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& valueTreeState;
    PhaserAudioProcessor& audioProcessor;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    // Dry/Wet mix
    juce::Slider drywetSlider;
    juce::Label  drywetLabel;
    std::unique_ptr<SliderAttachment> drywetSliderAttachment;

    // Rate L (LFO speed for left channel)
    juce::Slider rateLSlider;
    juce::Label  rateLLabel;
    std::unique_ptr<SliderAttachment> rateLSliderAttachment;

    // Rate R (LFO speed for right channel)
    juce::Slider rateRSlider;
    juce::Label  rateRLabel;
    std::unique_ptr<SliderAttachment> rateRSliderAttachment;

    // Intensity (modulation depth)
    juce::Slider intensitySlider;
    juce::Label  intensityLabel;
    std::unique_ptr<SliderAttachment> intensitySliderAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserAudioProcessorEditor)
};