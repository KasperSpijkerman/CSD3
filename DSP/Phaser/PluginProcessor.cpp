#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PhaserAudioProcessor::PhaserAudioProcessor()
        :
// Initializing the AudioProcessor and Value Tree State for parameters
        AudioProcessor (BusesProperties()
                                .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                                .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
        ), apvts(*this, nullptr,"Parameters", createParameters())
{
    // Getting the parameter values and storing them.
    dryWet = apvts.getRawParameterValue("drywet");
    rate = apvts.getRawParameterValue("rate");
    depth = apvts.getRawParameterValue("depth");
    intensity = apvts.getRawParameterValue("intensity");
}

PhaserAudioProcessor::~PhaserAudioProcessor()
{
}

//==============================================================================
const juce::String PhaserAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PhaserAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PhaserAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PhaserAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double PhaserAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PhaserAudioProcessor::getNumPrograms()
{
    return 1; // Some hosts require at least 1 program
}

int PhaserAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PhaserAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PhaserAudioProcessor::getProgramName (int index)
{
    return {};
}

void PhaserAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PhaserAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Prepare the Phaser effect with the sample rate
    phaserEffect.prepareToPlay(sampleRate);

    // Setting smoothing ramp time for adjusting the parameters smoothly
    previousDryWet.reset(sampleRate, 0.005);
    previousRate.reset(sampleRate, 0.005);
    previousDepth.reset(sampleRate, 0.005);
    previousIntensity.reset(sampleRate, 0.005);
}

void PhaserAudioProcessor::releaseResources()
{
    // This can be used to free resources when the audio stops.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PhaserAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
}
#endif

void PhaserAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Retrieve the current values of the parameters in real-time
    auto currentDryWet = *dryWet;
    auto currentRate = *rate;
    auto currentDepth = *depth;
    auto currentIntensity = *intensity;

    // Set smoothed target values for the parameters
    previousDryWet.setTargetValue(currentDryWet);
    previousRate.setTargetValue(currentRate);
    previousDepth.setTargetValue(currentDepth);
    previousIntensity.setTargetValue(currentIntensity);

    // Set the parameters in the Phaser effect
    phaserEffect.setDryWet(previousDryWet.getNextValue());
    phaserEffect.setRate(previousRate.getNextValue());
    phaserEffect.setIntensity(previousIntensity.getNextValue());

    // Clearing any output channels that are not used
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Processing the audio for each channel
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = phaserEffect.output(buffer.getSample(channel, sample), channel) * mainVolume;
        }
    }
}

//==============================================================================
bool PhaserAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* PhaserAudioProcessor::createEditor()
{
    return new PhaserAudioProcessorEditor(*this, apvts);
}

//==============================================================================
void PhaserAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PhaserAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PhaserAudioProcessor();
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout PhaserAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Creating parameters for the Phaser
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywet", 1 }, "Dry-Wet", 0.0f, 1.0f, 0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"rate", 2}, "Rate", 0.0f, 5.0f, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"depth", 3}, "Depth", 0.0f, 4.0f, 0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"intensity", 4}, "Intensity", 0.0f, 10.0f, 1.0f));

    return { params.begin(), params.end() };
}