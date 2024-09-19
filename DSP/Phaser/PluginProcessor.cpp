#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FlangerAudioProcessor::FlangerAudioProcessor()
:
// giving the Audio value tree state to the constructor and calling the createParameters function for all parameters, nullptr for undo manager so it won't be used.
    AudioProcessor (BusesProperties()
                   .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                   .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                   ), apvts(*this, nullptr,"Parameters", createParameters())
{
    // getting the parametervalues and storing them.
     dryWet = apvts.getRawParameterValue("drywet");
     feedback = apvts.getRawParameterValue("feedback");
     rateL = apvts.getRawParameterValue("ratel");
     rateR = apvts.getRawParameterValue("rater");
     depthL = apvts.getRawParameterValue("depthl");
     depthR = apvts.getRawParameterValue("depthr");
     intensity = apvts.getRawParameterValue("intensity");
}

FlangerAudioProcessor::~FlangerAudioProcessor()
{
}

//==============================================================================
const juce::String FlangerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FlangerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FlangerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FlangerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FlangerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FlangerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FlangerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FlangerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FlangerAudioProcessor::getProgramName (int index)
{
    return {};
}

void FlangerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FlangerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (Flanger& flanger : flangers)
    {
       flanger.prepareToPlay(sampleRate);
    }
    // setting the time for the ramp of adjusting the values
    previousdryWet.reset(sampleRate,0.005);
    previousfeedback.reset(sampleRate,0.005);
    previousrateL.reset(sampleRate,0.005);
    previousrateR.reset(sampleRate,0.005);
    previousdepthL.reset(sampleRate,0.005);
    previousdepthR.reset(sampleRate,0.005);
    previousintensity.reset(sampleRate,0.005);
}

void FlangerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FlangerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FlangerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    // retrieving the current values in realtime
    auto currentDryWet = *dryWet * 1.0f;
    auto currentFeedback = *feedback * 1.0f;
    auto currentrateL = *rateL * 1.0f;
    auto currentrateR = *rateR * 1.0f;
    auto currentdepthL = *depthL * 1.0f;
    auto currentdepthR= *depthR * 1.0f;
    auto currentIntensity = *intensity * 1.0f;

    // setting the current values targets to climb to smoothly
    previousdryWet.setTargetValue(currentDryWet);
    previousfeedback.setTargetValue(currentFeedback);
    previousrateL.setTargetValue(currentrateL);
    previousrateR.setTargetValue(currentrateR);
    previousdepthL.setTargetValue(currentdepthL);
    previousdepthR.setTargetValue(currentdepthR);
    previousintensity.setTargetValue(currentIntensity);

    // setting parameters for the flanger
    for (Flanger& flanger : flangers)
    {
        flanger.setDryWet(previousdryWet.getNextValue());
        flanger.setFeedback(previousfeedback.getNextValue());
        flanger.setRate(previousrateL.getNextValue(),previousrateR.getNextValue());
        flanger.setampDepth(previousrateL.getNextValue(),previousrateR.getNextValue());
        flanger.setIntensity(previousintensity.getNextValue());
    }
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        // process the audio
        for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = flangers[channel].output(buffer.getSample(channel,sample),channel)*mainVolume;
        }
    }
}

//==============================================================================
bool FlangerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FlangerAudioProcessor::createEditor()
{
    return new FlangerAudioProcessorEditor (*this,apvts);
}

//==============================================================================
void FlangerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

// keeping the state of the parameters
void FlangerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FlangerAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout FlangerAudioProcessor::createParameters()
{
    // creating a vector for all parameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    // creating every parameter that is going to be controlled, id to identify, actual name, range and default value
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywet", 1 }, "Dry-Wet", 0.0f, 1.0f,1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"feedback",2}, "Feedback", 0.0f, 0.90f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"ratel",3}, "Rate-L", 0.0f, 5.0f,1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"rater",4}, "Rate-R", 0.0f, 5.0f,1.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"depthl",5}, "Depth-L", 0.0f, 4.0f,0.3f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"depthr",6}, "Depth-R", 0.0f, 4.0f,0.3f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"intensity",7}, "Intensity", 0.0f, 20.0f,1));
    // returning the whole vector with parameters
    return {params.begin(), params.end()};
}