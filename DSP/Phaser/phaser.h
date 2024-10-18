#pragma once
#include "effect.h"
#include "sineOscillator.h"
#include "AllPassFilter.h"  // Include the all-pass filter class
#include "circBuffer.h"
#include <juce_core/juce_core.h>

class Phaser : public Effect
{
public:
    Phaser();
    ~Phaser();

    void prepareToPlay(double sampleRate) override;
    float output(float input, int channel);
    float smoothingFunction(float input);
    void setIntensity(float intensity);
    void setRate(float rateL, float rateR);
    void setDryWet(float mix);
    void calcMod(int channel);

private:
    SineOscillator oscillators[2];

    // Using five all-pass filters for each channel
    AllPassFilter allPassFilters[2][5];
    CircBuffer delayBuffer[2]; // Two channels (stereo)
    // Parameters
    float intensity { 0.5f };
    float rateL { 0.5f };
    float rateR { 0.5f };
    // Add this line for the maximum delay time (in seconds)
    float maxDelayTime { 0.01f }; // Adjust this value as needed (10ms delay, for example)

    double samplerateFX { 0.0 }; // Store the sample rate for future calculations
};
