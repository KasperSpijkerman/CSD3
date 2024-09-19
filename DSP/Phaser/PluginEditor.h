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
*/

// class with inheritance from OSCreceiver
class FlangerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              public FlangerAudioProcessor,
                                              private juce::OSCReceiver, // [1]
                                              private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback> // [2]
{

public:
    FlangerAudioProcessorEditor (FlangerAudioProcessor&,juce::AudioProcessorValueTreeState&);
    ~FlangerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    // value treestate for parameters.
    juce::AudioProcessorValueTreeState& valueTreeState;
    // short
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    //creating the sliders with labels for parameter control
    // dry wet
    juce::Slider drywetSlider;
    juce::Label  drywetLabel;
    std::unique_ptr<SliderAttachment> drywetSliderAttachment;
    // feedback
    juce::Slider feedbackSlider;
    juce::Label  feedbackLabel;
    std::unique_ptr<SliderAttachment> feedbackSliderAttachment;
    // rate L
    juce::Slider rateLSlider;
    juce::Label  rateLLabel;
    std::unique_ptr<SliderAttachment> rateLSliderAttachment;
    // rate R
    juce::Slider rateRSlider;
    juce::Label  rateRLabel;
    std::unique_ptr<SliderAttachment> rateRSliderAttachment;
    // depth L
    juce::Slider depthLSlider;
    juce::Label  depthLLabel;
    std::unique_ptr<SliderAttachment> depthLSliderAttachment;
    // depth R
    juce::Slider depthRSlider;
    juce::Label  depthRLabel;
    std::unique_ptr<SliderAttachment> depthRSliderAttachment;
    // intensity
    juce::Slider intensitySlider;
    juce::Label  intensityLabel;
    std::unique_ptr<SliderAttachment> intensitySliderAttachment;

    // osc receiver
    juce::OSCReceiver oscReceiver;

    // utilities
    Util util;

    // compass counter, rotations
    bool tippingpoint{false};
    float compassRotations {0};
    int rotationFactor{0};

    // Functions OSC
    void oscMessageReceived (const juce::OSCMessage& message) override;
    void showConnectionErrorMessage (const juce::String& messageText);
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FlangerAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerAudioProcessorEditor)
};
