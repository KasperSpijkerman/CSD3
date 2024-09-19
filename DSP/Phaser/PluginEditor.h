/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "utilities.h"

//==============================================================================
/**
*   The Phaser Audio Processor Editor class
*/
class PhaserAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PhaserAudioProcessorEditor (PhaserAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~PhaserAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Reference to the value tree state for parameters.
    juce::AudioProcessorValueTreeState& valueTreeState;

    // Shortcut for Slider Attachment
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    // Creating the sliders with labels for parameter control
    // Dry/Wet mix
    juce::Slider drywetSlider;
    juce::Label  drywetLabel;
    std::unique_ptr<SliderAttachment> drywetSliderAttachment;

    // Rate (LFO speed)
    juce::Slider rateSlider;
    juce::Label  rateLabel;
    std::unique_ptr<SliderAttachment> rateSliderAttachment;

    // Intensity (modulation depth)
    juce::Slider intensitySlider;
    juce::Label  intensityLabel;
    std::unique_ptr<SliderAttachment> intensitySliderAttachment;

    // Depth (controls the depth of the modulation)
    juce::Slider depthSlider;
    juce::Label  depthLabel;
    std::unique_ptr<SliderAttachment> depthSliderAttachment;

    // Reference to the processor
    PhaserAudioProcessor& audioProcessor;

    // Utility class (if still needed)
    Util util;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserAudioProcessorEditor)
};