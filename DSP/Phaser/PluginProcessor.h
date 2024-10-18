/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "phaser.h"

//==============================================================================
/**
*/
class PhaserAudioProcessor  : public juce::AudioProcessor
#if JucePlugin_Enable_ARA
    , public juce::AudioProcessorARAExtension
#endif
{
public:
    //==============================================================================
    PhaserAudioProcessor();
    ~PhaserAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // Creating a Value Tree State object for controlling parameters.
    juce::AudioProcessorValueTreeState apvts;

    // Phaser object to handle processing for both channels
    Phaser phaserEffect;

private:
    // Creating smoothed values for every parameter
    juce::SmoothedValue<float> previousDryWet {0.0f};
    juce::SmoothedValue<float> previousRateL { 0.0f };
    juce::SmoothedValue<float> previousRateR { 0.0f };
    juce::SmoothedValue<float> previousIntensity {0.0f};

    // The actual real-time atomic float values of parameters, initialized with null pointers for protection
    std::atomic<float>* dryWet = nullptr;
    std::atomic<float>* rateL = nullptr;
    std::atomic<float>* rateR = nullptr;
    std::atomic<float>* intensity = nullptr;

    // Main volume variable
    float mainVolume = 0.8f;

    // Function to create the parameter layout for the Value Tree State
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserAudioProcessor)
};