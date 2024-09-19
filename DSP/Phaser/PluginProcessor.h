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
class FlangerAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    FlangerAudioProcessor();
    ~FlangerAudioProcessor() override;

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

    // creating a Value Tree State object for controlling parameters.
    juce::AudioProcessorValueTreeState apvts;
    // creating 2 flanger objects for stereo-flanger
    std::array<Flanger, 2> flangers;



private:
    // creating smoothed values for every parameter
    juce::SmoothedValue<float> previousdryWet {0.0f};
    juce::SmoothedValue<float>  previousfeedback {0.0f};
    juce::SmoothedValue<float>  previousrateL {0.0f};
    juce::SmoothedValue<float>  previousrateR {0.0f};
    juce::SmoothedValue<float>  previousdepthL {0.0f};
    juce::SmoothedValue<float>  previousdepthR {0.0f};
    juce::SmoothedValue<float>  previousintensity{0.0f};

    // the actual realtime atomic float values of parameters, init with nullpointer for protection
    std::atomic<float>* dryWet = nullptr;
    std::atomic<float>* feedback  = nullptr;
    std::atomic<float>* rateL = nullptr;
    std::atomic<float>*  rateR = nullptr;
    std::atomic<float>*  depthL = nullptr;
    std::atomic<float>* depthR  = nullptr;
    std::atomic<float>* intensity  = nullptr;

    // mainvolume variabele
    float mainVolume = 0.8f;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerAudioProcessor)
};
