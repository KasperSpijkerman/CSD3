#pragma once
#include "sineOscillator.h"
#include "AllPassFilter.h"

class Phaser {
public:
    Phaser();
    ~Phaser();

    void prepareToPlay(double sampleRate);
    float output(float input, int channel);
    void setIntensity(float intensity);
    void setRate(float rateL, float rateR);
    void setDryWet(float mix);

private:
    void updateLFO(int channel);

    SineOscillator oscillators[2]; // Two LFOs for stereo
    AllPassFilter allPassFilters[2][5]; // Five all-pass filters per channel

    float intensity { 0.5f };
    float dry { 0.5f };
    float wet { 0.5f };
    double sampleRate { 44100.0 }; // Default sample rate

    float smoothingFunction(float input);
};
