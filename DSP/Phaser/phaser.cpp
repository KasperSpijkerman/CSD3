#include "phaser.h"

// Constructor
Phaser::Phaser()
{
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
    for (Oscillator& oscillator : oscillators)
    {
        oscillator.setSamplerate(samplerateFX);
    }

    // Initialize the dry/wet mix (inherited from Effect base class)
    setDryWet(0.5f);  // Default dry/wet to 50% wet
}

// Calculate modulation signal and apply it to the all-pass filters for each channel
void Phaser::calcMod(int channel)
{
    // Tick the oscillator for this channel (LFO for modulating the filters)
    oscillators[channel].tick();

    // Get the modulation signal from the oscillator (typically a sine or triangle wave)
    float modulationSignal = (oscillators[channel].getSample() + 1.0f) / 2.0f;  // Normalize to [0, 1]

    // Adjust the all-pass filter cutoff frequency based on the modulation signal
    // Placeholder: You will implement the all-pass filter logic in the output function
    for (int i = 0; i < 4; ++i)
    {
        // Example: Modulate the cutoff frequency of each filter in the chain
        allPassFilters[channel][i] = modulationSignal * intensity;
    }
}

// Process the audio sample (apply phaser effect)
float Phaser::output(float input, int channel)
{
    // Calculate modulation for the current channel
    calcMod(channel);

    // Process the input through all-pass filters (basic example, adjust with real implementation)
    float processedSignal = input;
    for (int i = 0; i < 4; ++i)
    {
        // Simple all-pass filter placeholder (replace with actual filter processing)
        // Normally you would process the input through actual all-pass filters here
        processedSignal = allPassFilters[channel][i] * processedSignal + input * (1.0f - allPassFilters[channel][i]);
    }

    // Apply dry/wet mix (blend processed signal with the original input)
    return (input * dry) + (processedSignal * wet);  // dry and wet inherited from Effect class
}

// Set the intensity (modulation depth)
void Phaser::setIntensity(float intensity)
{
    this->intensity = intensity;
}

// Set the modulation rate (speed of the LFO)
void Phaser::setRate(float rateL, float rateR)
{
    oscillators[0].setFrequency(rateL);
    oscillators[1].setFrequency(rateR);
}

// Set the dry/wet mix (this overrides the base class method)
void Phaser::setDryWetMix(float mix)
{
    setDryWet(mix);  // Call the base class method to handle dry/wet logic
}