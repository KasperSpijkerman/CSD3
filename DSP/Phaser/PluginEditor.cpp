#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PhaserAudioProcessorEditor::PhaserAudioProcessorEditor (PhaserAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
        : AudioProcessorEditor (&p), valueTreeState(vts), audioProcessor(p)
{
    // Dry/Wet slider and label
    drywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 25);
    drywetSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "drywet", drywetSlider);
    drywetSlider.setTextValueSuffix(" Dry/Wet");
    drywetLabel.setText("Dry-Wet", juce::dontSendNotification);
    drywetLabel.attachToComponent(&drywetSlider, true);
    drywetLabel.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(drywetSlider);

    // Rate L slider and label (for left channel LFO)
    rateLSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateLSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 25);
    rateLSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ratel", rateLSlider);
    rateLSlider.setTextValueSuffix(" Rate L");
    rateLLabel.setText("Rate L", juce::dontSendNotification);
    rateLLabel.attachToComponent(&rateLSlider, true);
    rateLLabel.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(rateLSlider);

    // Rate R slider and label (for right channel LFO)
    rateRSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateRSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 25);
    rateRSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "rater", rateRSlider);
    rateRSlider.setTextValueSuffix(" Rate R");
    rateRLabel.setText("Rate R", juce::dontSendNotification);
    rateRLabel.attachToComponent(&rateRSlider, true);
    rateRLabel.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(rateRSlider);

    // Depth slider and label
    depthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 25);
    depthSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "depth", depthSlider);
    depthSlider.setTextValueSuffix(" Depth");
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.attachToComponent(&depthSlider, true);
    depthLabel.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(depthSlider);

    // Intensity slider and label
    intensitySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    intensitySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 25);
    intensitySliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "intensity", intensitySlider);
    intensitySlider.setTextValueSuffix(" Intensity");
    intensityLabel.setText("Intensity", juce::dontSendNotification);
    intensityLabel.attachToComponent(&intensitySlider, true);
    intensityLabel.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(intensitySlider);

    // Set the size of the plugin window
    setSize(600, 400);
}

PhaserAudioProcessorEditor::~PhaserAudioProcessorEditor()
{
}

//==============================================================================
void PhaserAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Fill the background with a color
    g.fillAll(juce::Colours::darkgrey);

    // Set the font and text color
    g.setFont(juce::Font("Helvetica", 40.0f, juce::Font::bold));
    g.setColour(juce::Colours::lightblue);

    // Draw the plugin title
    g.drawText("Phaser", getLocalBounds().removeFromTop(100), juce::Justification::centred, true);
}

//==============================================================================
void PhaserAudioProcessorEditor::resized()
{
    // Layout the sliders
    drywetSlider.setBounds(50, 150, 150, 150);
    rateLSlider.setBounds(250, 150, 150, 150);  // Rate L slider (Left)
    rateRSlider.setBounds(450, 150, 150, 150);  // Rate R slider (Right)
    depthSlider.setBounds(50, 300, 150, 150);   // Depth slider
    intensitySlider.setBounds(250, 300, 150, 150);  // Intensity slider

    // Set the slider thumb color
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::deeppink);
}
