/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
FlangerAudioProcessorEditor::FlangerAudioProcessorEditor (FlangerAudioProcessor& p,juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState (vts), audioProcessor (p)
{

    // dry wet slider and label
    drywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    drywetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "drywet",drywetSlider);
    drywetSlider.setTextValueSuffix (" Dry-wet");
    // labels for text attached to slider
    drywetLabel.setText ("Dry-Wet", juce::dontSendNotification);
    drywetLabel.attachToComponent (&drywetSlider, true);
    drywetLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(drywetSlider);

    // feedback slider and label
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    feedbackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "feedback",feedbackSlider);
    feedbackSlider.setTextValueSuffix (" Feedback");
    // labels for text attached to slider
    feedbackLabel.setText ("Feedback", juce::dontSendNotification);
    feedbackLabel.attachToComponent (&feedbackSlider, true);
    feedbackLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(feedbackSlider);


    // rate L slider and label
    rateLSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateLSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    rateLSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ratel",rateLSlider);
    rateLSlider.setTextValueSuffix (" Rate L");
    // labels for text attached to slider
    rateLLabel.setText ("Rate L", juce::dontSendNotification);
    rateLLabel.attachToComponent (&rateLSlider, true);
    rateLLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(rateLSlider);

    // rate R slider and label
    rateRSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateRSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    rateRSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "rater",rateRSlider);
    rateRSlider.setTextValueSuffix (" Rate R");
    // labels for text attached to slider
    rateRLabel.setText ("Rate R", juce::dontSendNotification);
    rateRLabel.attachToComponent (&rateRSlider, true);
    rateRLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(rateRSlider);

    // rate R slider and label
    depthLSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthLSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    depthLSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "depthl",depthLSlider);
    depthLSlider.setTextValueSuffix (" Depth L");
    // labels for text attached to slider
    depthLLabel.setText ("Depth L", juce::dontSendNotification);
    depthLLabel.attachToComponent (&depthLSlider, true);
    depthLLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(depthLSlider);

    // rate R slider and label
    depthRSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthRSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    depthRSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "depthr",depthRSlider);
    depthRSlider.setTextValueSuffix (" Depth R");
    // labels for text attached to slider
    depthRLabel.setText ("Depth R", juce::dontSendNotification);
    depthRLabel.attachToComponent (&depthRSlider, true);
    depthRLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(depthRSlider);

    // rate R slider and label
    intensitySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    intensitySlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    intensitySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "intensity",intensitySlider);
    intensitySlider.setTextValueSuffix (" Intensity");
    // labels for text attached to slider
    intensityLabel.setText ("Intensity", juce::dontSendNotification);
    intensityLabel.attachToComponent (&intensitySlider, true);
    intensityLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(intensitySlider);

    // OSC Port
    if (! connect (7779))
    {
        // showing error if it is not connected
        showConnectionErrorMessage ("Error: could not connect to UDP port 7779.");
    }
    // adding listeners for the parameters.
    juce::OSCReceiver::addListener(this, "/ZIGSIM/1234/compass");
    juce::OSCReceiver::addListener(this, "/ZIGSIM/1234/touch02");
    juce::OSCReceiver::addListener(this, "/ZIGSIM/1234/facemouthsmileleft");

    // setting size of canvas.
    setSize (800, 800);

}

FlangerAudioProcessorEditor::~FlangerAudioProcessorEditor()
{}

//==============================================================================
void FlangerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // colors and text in the plugin window
    g.fillAll (juce::Colours::darkviolet);
    g.setFont (juce::Font ("New Times Roman", 83.0f, juce::Font::bold));
    g.setColour(juce::Colours::orange);
    g.drawText("SpinFlange",160,50,500,100,juce::Justification::centred);
    g.setFont (juce::Font ("New Times Roman", 80.0f, juce::Font::bold));
    g.setColour(juce::Colours::deepskyblue);
    g.drawText("SpinFlange",160,50,500,100,juce::Justification::centred);



}


void FlangerAudioProcessorEditor::resized()
{
    // layout sliders
    drywetSlider.setBounds(getWidth() / 8.2, getHeight() / 2.0, 200, 100);
    feedbackSlider.setBounds(getWidth() / 1.4, getHeight() / 2.0, 200, 100);
    rateLSlider.setBounds(getWidth() / 8.2, getHeight() / 4.0, 200, 100);
    rateRSlider.setBounds(getWidth() / 1.4, getHeight() / 4.0, 200, 100);
    depthLSlider.setBounds(getWidth() / 8.2, getHeight() / 1.2, 200, 100);
    depthRSlider.setBounds(getWidth() / 1.4, getHeight() / 1.2, 200, 100);
    intensitySlider.setBounds(getWidth() / 2.5, getHeight() / 1.2, 200, 100);

    // set the color to red
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::deeppink);
}

// Function for receiving OSC and getting the messages.
void FlangerAudioProcessorEditor::oscMessageReceived (const juce::OSCMessage& message)
{
    if (message.size() == 1 && message[0].isFloat32())   {}
    OSCAddressPattern compassPattern("/ZIGSIM/1234/compass");
    OSCAddressPattern touch02Pattern("/ZIGSIM/1234/touch02");
    OSCAddressPattern smilePattern("/ZIGSIM/1234/facemouthsmileleft");

    OSCAddress messageAddress(message.getAddressPattern().toString());

    if (compassPattern.matches(messageAddress))
    {
        // receiving compass with 360 and creating variabele for one full rotation
        float compassOneRotation = util.mapInRange(message[0].getFloat32(),0,360,0,100.0f);
        // degrees for feedback scaling it according to rotationfactor
        float degreesFB = (message[0].getFloat32()+(rotationFactor * 360));
        float degreesRate = (message[0].getFloat32()+(compassRotations * 360));
        // scaling feedback according to 4 max rotations, making it more dynamic
        float feedbackCOSC = util.mapInRange(degreesFB,1,1080,0,0.90);
        // scaling feedback according to 6 max rotations, making it more dynamic
        float rateOSC = util.mapInRange(degreesRate,1,1440,0,0.99);
        feedbackSlider.setValue (juce::jlimit (0.0f, 0.90f,feedbackCOSC ));
        rateLSlider.setValue(juce::jlimit (0.1f, 4.9f, rateOSC));
        rateRSlider.setValue(juce::jlimit (0.0f, 5.0f, rateOSC));

        if(compassOneRotation>95.0)
        {
            tippingpoint = true;
        }

        if(tippingpoint&&compassOneRotation < 3.0)
        {
            compassRotations++;
            rotationFactor++;
            tippingpoint = false;
        }
        if (compassRotations >4)
        {
            compassRotations = 0;
        }

        if (rotationFactor > 3)
        {
            rotationFactor = 0;
        }



    }
    // comparing messages to touch02 (y coordinate) address and changing intensity slider
    if (touch02Pattern.matches(messageAddress))
    {
        // intensity changing based on y coordinate
        float yCoordinate = message[0].getFloat32();
        float intensityOSC = util.mapInRange(yCoordinate,-1,1,20,1);

        intensitySlider.setValue (juce::jlimit (0.0f, 20.0f, intensityOSC));
    }

    if (smilePattern.matches(messageAddress))
    {
        // toggle for smiling changing the dry wet
        bool drywet = false;
        bool currentState = false;
        bool previousState = false;
        bool smile = false;
        float drywetOSC {0};

        if(message[0].getFloat32() > 0.3)
        {
            smile = true;
        }
        else
        {
            smile = false;
        }
        currentState = smile;

        if (previousState != currentState)
        {
            if (smile)
            {
                drywet = !drywet;
            }
            previousState = currentState;
        }
        if (drywet)
        {
            drywetOSC = 0.2;
        }
        else
        {

            drywetOSC = 0.8;
        }
        drywetSlider.setValue (juce::jlimit (0.0f, 20.0f,drywetOSC));
    }
}

// debug OSC connection
void FlangerAudioProcessorEditor::showConnectionErrorMessage (const juce::String& messageText)
{
    juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                            "Connection error",
                                            messageText,
                                            "OK");
}