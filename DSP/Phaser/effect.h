#pragma once
#include <iostream>

class Effect
{
public:
    // prepare to play and dry wet
    virtual void prepareToPlay (double sampleRate) = 0;
    void setDryWet(float dryWet);
protected:
    // dry and wet for every effect
    float dry { 0 };
    float wet { 0 };
    // empty samplerate var for every effect, will be overwritten by actual samplerate of host
    double samplerateFX { 0 };
};