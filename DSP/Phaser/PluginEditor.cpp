#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PhaserAudioProcessorEditor::PhaserAudioProcessorEditor (PhaserAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
        : AudioProcessorEditor (&p), valueTreeState(vts), audioProcessor(p)
{
    setResizable(true, true); // Allow resizable window
    setResizeLimits(300, 200, 1200, 800); // Set min/max window size
    getConstrainer()->setFixedAspectRatio(1.5); // Keep a consistent aspect ratio

    // Dry/Wet slider and label
    drywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    drywetSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "drywet", drywetSlider);
    drywetSlider.setTextValueSuffix(" Dry/Wet");
    drywetLabel.setText("Dry-Wet", juce::dontSendNotification);
    drywetLabel.attachToComponent(&drywetSlider, false);
    addAndMakeVisible(drywetSlider);

    // Rate L slider and label (for left channel LFO)
    rateLSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateLSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    rateLSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ratel", rateLSlider);
    rateLLabel.setText("Rate L", juce::dontSendNotification);
    rateLLabel.attachToComponent(&rateLSlider, false);
    addAndMakeVisible(rateLSlider);

    // Rate R slider and label (for right channel LFO)
    rateRSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateRSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    rateRSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "rater", rateRSlider);
    rateRLabel.setText("Rate R", juce::dontSendNotification);
    rateRLabel.attachToComponent(&rateRSlider, false);
    addAndMakeVisible(rateRSlider);

    // Intensity slider and label
    intensitySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    intensitySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    intensitySliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "intensity", intensitySlider);
    intensityLabel.setText("Intensity", juce::dontSendNotification);
    intensityLabel.attachToComponent(&intensitySlider, false);
    addAndMakeVisible(intensitySlider);

    // Set the size of the plugin window
    setSize(600, 400);
}

PhaserAudioProcessorEditor::~PhaserAudioProcessorEditor() {}

//==============================================================================
void PhaserAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Vibrant purple and dark cyan gradient background
    juce::ColourGradient backgroundGradient(juce::Colours::purple, 0, 0, juce::Colours::darkcyan, getWidth(), getHeight(), false);
    g.setGradientFill(backgroundGradient);
    g.fillAll();

    // Dynamically calculate the title font size based on the height of the window
    float titleFontSize = getHeight() / 10.0f;

    // Use the default sans-serif font
    juce::Font titleFont(titleFontSize, juce::Font::bold);
    g.setFont(titleFont);

    // Create a gradient for the title text that matches the colors of the knobs
    juce::ColourGradient titleGradient(juce::Colours::hotpink, 0, 0, juce::Colours::lightblue, getWidth(), getHeight(), false);
    titleGradient.addColour(0.5, juce::Colours::blueviolet);  // Adding a middle gradient stop

    // Add shadow to the title text (slightly offset black text)
    g.setColour(juce::Colours::black.withAlpha(0.5f));  // Shadow color
    g.drawText("PhaseWave", getLocalBounds().removeFromTop(getHeight() / 5).translated(4, 4), juce::Justification::centred, true);

    // Add glow effect (subtle offset white text with low opacity)
    g.setColour(juce::Colours::white.withAlpha(0.1f));  // Subtle glow
    g.drawText("PhaseWave", getLocalBounds().removeFromTop(getHeight() / 5).translated(-3, -3), juce::Justification::centred, true);

    // Finally, draw the actual title with the gradient fill
    g.setGradientFill(titleGradient);
    g.drawText("PhaseWave", getLocalBounds().removeFromTop(getHeight() / 5), juce::Justification::centred, true);
}

void PhaserAudioProcessorEditor::resized()
{
    // Get the total available width and height of the window
    int totalWidth = getWidth();
    int totalHeight = juce::jmax(400, getHeight());  // Set a minimum height to avoid overcrowding

    // Define the width and height for each knob
    int sliderWidth = totalWidth / 5;   // Dynamic width based on window size (5 knobs in total)
    int sliderHeight = juce::jmin(totalHeight / 3, 150); // Limit height to avoid the window being too small

    // Define the font size for the labels, dynamically adjusted based on window size
    float labelFontSize = juce::jmin(totalHeight / 25.0f, 15.0f);  // Limit label size dynamically

    // Create a Font object for the labels
    juce::Font labelFont(juce::Font::getDefaultSansSerifFontName(), labelFontSize, juce::Font::plain);

    // Apply the font to the labels
    drywetLabel.setFont(labelFont);
    rateLLabel.setFont(labelFont);
    rateRLabel.setFont(labelFont);
    intensityLabel.setFont(labelFont);

    // Adjust Y offset for labels to prevent overlap with knobs
    int labelHeight = 30;  // Set label height higher to prevent overlap with knobs

    // Layout the first row of sliders (Dry/Wet, Rate L, Rate R)
    int startX = (totalWidth - (sliderWidth * 3)) / 2;  // Center the first row (3 knobs)
    int startY = totalHeight / 4;  // Start below the title text area
    drywetSlider.setBounds(startX, startY, sliderWidth, sliderHeight);
    rateLSlider.setBounds(startX + sliderWidth, startY, sliderWidth, sliderHeight);
    rateRSlider.setBounds(startX + (sliderWidth * 2), startY, sliderWidth, sliderHeight);

    // Adjust label positions (above the sliders to prevent overlap)
    drywetLabel.setBounds(drywetSlider.getX(), drywetSlider.getY() - labelHeight, sliderWidth, labelHeight);
    rateLLabel.setBounds(rateLSlider.getX(), rateLSlider.getY() - labelHeight, sliderWidth, labelHeight);
    rateRLabel.setBounds(rateRSlider.getX(), rateRSlider.getY() - labelHeight, sliderWidth, labelHeight);

    // Layout the second row of sliders (Depth, Intensity)
    int secondRowY = juce::jmin(startY + sliderHeight + 40, totalHeight - sliderHeight - 60);  // Ensure it doesn't go out of bounds

    intensitySlider.setBounds(startX + (sliderWidth * 2), secondRowY, sliderWidth, sliderHeight); // Place on right

    // Adjust labels for the bottom sliders

    intensityLabel.setBounds(intensitySlider.getX(), intensitySlider.getY() - labelHeight, sliderWidth, labelHeight);

    // Set the text boxes (number boxes) under the sliders to resize dynamically
    int textBoxHeight = juce::jmin(totalHeight / 10, 40); // Dynamically calculate the height of the text boxes
    drywetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, sliderWidth, textBoxHeight);
    rateLSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, sliderWidth, textBoxHeight);
    rateRSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, sliderWidth, textBoxHeight);

    intensitySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, sliderWidth, textBoxHeight);

    // Set the slider thumb color and other look-and-feel properties
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::hotpink);
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightblue);
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::blueviolet);
}






