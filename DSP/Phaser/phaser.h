#pragma once
#include "effect.h"
#include "sineOscillator.h"
#include "AllPassFilter.h" // Include the new all-pass filter class
#include <juce_core/juce_core.h>

using namespace juce;

class Phaser : public Effect
{
public:
    Phaser();
    ~Phaser();

    void prepareToPlay(double sampleRate) override;
    float output(float input, int channel);
    void setIntensity(float intensity);
    void setRate(float rateL, float rateR);
    void setDryWetMix(float mix);
    void calcMod(int channel);

private:
    SineOscillator oscillators[2];

    // Using five all-pass filters for each channel
    AllPassFilter allPassFilters[2][5];

    // Parameters
    float intensity { 0.5f };
    float rateL { 0.5f };
    float rateR { 0.5f };
};
