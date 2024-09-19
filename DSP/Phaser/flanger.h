#pragma once
#include "effect.h"
#include "delay.h"
#include "triangle.h"

class Flanger : public Effect
{
    public:
        // constructor & deconstructor
        Flanger();
        ~Flanger();

        void prepareToPlay(double sampleRate) override;
        float output(float input,int channel);
        // setters
        // depth -> range for modulation
        void setIntensity(float depth);
        // depth for amplitude of the oscillators
        void setampDepth(float ampDepthL, float ampDepthR);
        void setRate(float rateL,float rateR);
        // calculating modulation and ticking oscillators
        void calcMod(int channel);

        void setFeedback(float flangeFeedback);
        // creating delays for stereo Flanger
        Delay delays[2] = {Delay(),Delay()};
        // creating triangle oscillator to modulate the delay, different frequency for stereo effect
        Triangle oscillators[2] = {Triangle(rateL,ampDepthL),Triangle(rateR,ampDepthR)};
    private:

        // delay range modulation depth, intensity of modulation
        float range { 0.0f };
        // depth for amplitude of the triangle oscillators
        float ampDepthL {0.0f};
        float ampDepthR {0.0f};
        // speed for modulation
        float rateL { 0.0f };
        float rateR {0.0f};
        // samplerate will be overwritten
        float sampleRateFX;
        float freq {0.0f};
        float flangeFeedback {0.0f};
};


