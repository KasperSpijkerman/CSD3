#include "oscillator.h"
#include "math.h"

Oscillator::Oscillator(float frequency, float amplitude) : frequency(frequency),
                                                           amplitude(amplitude), phase(0), sample(0)
{
}

Oscillator::~Oscillator()
{
}

void Oscillator::setSamplerate(float samplerate)
{
  this->samplerate = samplerate;
}

float Oscillator::getSample()
{
  return sample;
}

// getters and setters
void Oscillator::setFrequency(float frequency)
{
  this->frequency = frequency;
}

// getters and setters
void Oscillator::setAmplitude(float frequency)
{
    this->amplitude = amplitude;
}

float Oscillator::getFrequency()
{
  return frequency;
}

void Oscillator::tick()
{
  // increment the phase to allow calculation of next sample
  sample = phase += frequency / samplerate;
  // wrap the phase to interval [0, 1]
  if (phase > 1)
    phase -= 1.0;
  // calculate sample for the incremented phase
 calculate();
}