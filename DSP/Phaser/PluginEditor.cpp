#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PhaserAudioProcessorEditor::PhaserAudioProcessorEditor (PhaserAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
        : AudioProcessorEditor (&p), valueTreeState(vts), audioProcessor(p)
{
    // Dry/Wet slider and label
    drywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 25);
    drywetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "drywet", drywetSlider);
    drywetSlider.setTextValueSuffix(" Dry/Wet");
    drywetLabel.setText("Dry-Wet", juce::dontSendNotification);
    drywetLabel.attachToComponent(&drywetSlider, true);
    drywetLabel.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(drywetSlider);

    // Rate slider and label
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 25);
    rateSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "rate", rateSlider);
    rateSlider.setTextValueSuffix(" Rate");
    rateLabel.setText("Rate", juce::dontSendNotification);
    rateLabel.attachToComponent(&rateSlider, true);
    rateLabel.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(rateSlider);

    // Depth slider and label
    depthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 25);
    depthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "depth", depthSlider);
    depthSlider.setTextValueSuffix(" Depth");
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.attachToComponent(&depthSlider, true);
    depthLabel.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(depthSlider);

    // Intensity slider and label
    intensitySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    intensitySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 25);
    intensitySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "intensity", intensitySlider);
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
    rateSlider.setBounds(250, 150, 150, 150);
    depthSlider.setBounds(450, 150, 150, 150);
    intensitySlider.setBounds(250, 300, 150, 150);

    // Set the slider thumb color
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::deeppink);
}