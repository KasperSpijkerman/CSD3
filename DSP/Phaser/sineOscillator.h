#pragma once
#include <cmath>

class SineOscillator {
public:
    SineOscillator(float frequency = 440.0f, float amplitude = 1.0f, float samplerate = 44100.0f);

    void setFrequency(float newFrequency);
    void setAmplitude(float newAmplitude);
    void setSamplerate(float newSamplerate);
    float getSample();
    void tick();

private:
    float frequency;
    float amplitude;
    float samplerate;
    float phase { 0.0f };
    float sample { 0.0f };

    void calculate();
};
