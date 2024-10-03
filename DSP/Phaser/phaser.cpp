#include "phaser.h"

// Constructor
Phaser::Phaser()
{
    // Reset all filters to their initial state
    for (int ch = 0; ch < 2; ++ch)
    {
        for (int i = 0; i < 5; ++i)
        {
            allPassFilters[ch][i].reset();
        }
    }
}

// Destructor
Phaser::~Phaser()
{
}

// Prepare the phaser (set sample rate for oscillators, initialize any needed variables)
void Phaser::prepareToPlay(double sampleRate)
{
    this->samplerateFX = sampleRate;

    // Set the sample rate for the LFO oscillators
    for (SineOscillator& oscillator : oscillators)
    {
        oscillator.setSamplerate(samplerateFX);
    }

    // Default dry/wet to 50% wet
    setDryWet(0.5f);
}

// Calculate modulation signal and apply it to the all-pass filters for each channel
void Phaser::calcMod(int channel)
{
    // Tick the oscillator (LFO for modulating the filters)
    oscillators[channel].tick();

    // Modulation signal (sine wave, normalized to [0, 1])
    float modulationSignal = (oscillators[channel].getSample() + 1.0f) / 2.0f;

    // Set filter modulation coefficient
    for (int i = 0; i < 5; ++i)
    {
        // Modulate the all-pass filter coefficient 'g', safely clamped to 0.01 - 0.99
        float g = juce::jlimit(0.01f, 0.99f, modulationSignal * intensity);
        allPassFilters[channel][i].setCoefficient(g);
    }
}

// Process the audio sample (apply phaser effect)
float Phaser::output(float input, int channel)
{
    // Calculate modulation for the current channel
    calcMod(channel);

    // Process the input through the chain of all-pass filters
    float processedSignal = input;

    for (int i = 0; i < 5; ++i)
    {
        processedSignal = allPassFilters[channel][i].process(processedSignal);
    }

    // Apply dry/wet mix (blend processed signal with the original input)
    return (input * dry) + (processedSignal * wet);
}

// Set the intensity (modulation depth)
void Phaser::setIntensity(float newIntensity)
{
    this->intensity = juce::jlimit(0.0f, 1.0f, newIntensity);  // Keep intensity in a safe range
}

// Set the modulation rate (speed of the LFO)
void Phaser::setRate(float newRateL, float newRateR)
{
    oscillators[0].setFrequency(newRateL);
    oscillators[1].setFrequency(newRateR);
}

// Set the dry/wet mix (overrides base class)
void Phaser::setDryWetMix(float mix)
{
    setDryWet(mix);
}
