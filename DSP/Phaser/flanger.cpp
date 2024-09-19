#include "flanger.h"

Flanger::Flanger()
{
}
Flanger::~Flanger()
{
}
// prepare to play for delays and oscillators
void Flanger::prepareToPlay(double sampleRate)
{
        for (Delay& delay : delays)
        {
            delay.prepareToPlay(sampleRate);
            delay.setDelayTime(range);
        }

        for (Triangle& oscillator : oscillators)
        {
            oscillator.setSamplerate(sampleRate);
        }
        // setting dry wet
        setDryWet(0.0f);
        // setting the feedback
        setFeedback(flangeFeedback);
}

//  ticking the oscillators and calculating modulation for both
void Flanger::calcMod(int channel)
{
    //ticking both oscillators
    oscillators[channel].tick();
    // calculating mod signal, making it unipolar
    float modulationSignal = (oscillators[channel].getSample() +1) / 2;
    // setting the delay time based on depth.
    delays[channel].setDelayTime(range * modulationSignal);
}

// giving the input and channel to output function
float Flanger::output(float input,int channel =0)
{
    // calculating the modulation and giving output based on input and dry wet
    calcMod(channel);
    return input * dry + delays[channel].output(input) * wet;
}
// setting intensity, aka range delay
void Flanger::setIntensity(float range)
{
    this->range = range;
}

void Flanger::setRate(float rateL, float rateR)
{
        oscillators[0].setFrequency(rateL);
        oscillators[1].setFrequency(rateR);
}
void Flanger::setampDepth(float ampDepthL, float ampDepthR)
{
    oscillators[0].setAmplitude(ampDepthL);
    oscillators[1].setAmplitude(ampDepthR);
}




void Flanger::setFeedback(float flangeFeedback)
{
    for (Delay& delay : delays)
    {
        delay.setFeedback(flangeFeedback);
    }
}
