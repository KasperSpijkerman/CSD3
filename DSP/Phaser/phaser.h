#pragma once
#include "effect.h"
#include "oscillator.h"  // LFO to modulate the all-pass filters

class Phaser : public Effect
{
public:
    // Constructor & Destructor
    Phaser();
    ~Phaser();

    // Prepare the phaser for playback (set sample rate, initialize filters)
    void prepareToPlay(double sampleRate) override;

    // Process the audio sample, called every time a sample needs to be processed
    float output(float input, int channel);

    // Set the modulation depth (intensity of the phase effect)
    void setIntensity(float intensity);

    // Set the speed (rate) of the LFO for both channels
    void setRate(float rateL, float rateR);

    // Set the dry/wet mix ratio (override from base class)
    void setDryWetMix(float mix);

    // Calculate modulation and update the phase shifting for each channel
    void calcMod(int channel);

private:
    // LFOs for modulating all-pass filters
    Oscillator oscillators[2] = { Oscillator(rateL), Oscillator(rateR) };

    // All-pass filters for each channel (for a stereo effect)
    float allPassFilters[2][4];  // Example: using 4 all-pass filters per channel

    // Parameters for the Phaser
    float intensity { 0.5f };  // Modulation depth (how strong the phase shift is)
    float rateL { 0.5f };      // LFO rate for left channel
    float rateR { 0.5f };      // LFO rate for right channel
};