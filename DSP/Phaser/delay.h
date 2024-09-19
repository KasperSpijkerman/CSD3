#pragma once
#include "circBuffer.h"

class Delay : public Effect 
{
public:
	Delay();
	~Delay();

    float output(float input) ;
	void prepareToPlay(double samplerate) override;
	// function for converting miliseconds to samples 
	float msToSamp(float ms, double samplerate);
    void deleteBuffer();

	// setters
	void setDelayTime(float delayTime);
	void setFeedback(float feedback);

private:
	// creating a circbuffer pointer
    CircBuffer* delayBuffer;
    // delay time in miliseconds
	float delayTimeMs { 0 };
    // delay in samples
	float delaySamples { 0 };
    // output
	float outputDelay { 0 };
    // feedback amount
	float delayFeedback { 0 };
};