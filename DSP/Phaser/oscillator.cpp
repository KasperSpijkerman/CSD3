#include "oscillator.h"
#include "math.h"

Oscillator::Oscillator(float frequency, float amplitude)
        : frequency(frequency), amplitude(amplitude)
{
    this->frequency = frequency;
    this->amplitude = amplitude;
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

void Oscillator::tick() {
    // Example of 2x oversampling
    float originalFrequency = frequency;
    float originalSample = sample;

    // Perform the upsampling process
    for (int i = 0; i < 2; ++i) {
        sample = phase += (frequency * 2) / samplerate;  // Multiply frequency by oversampling factor
        if (phase > 1) {
            phase -= 1.0;
        }
        calculate();  // Produce the oversampled wave
    }

    // Low-pass filter the oversampled wave (simple averaging)
    sample = (originalSample + sample) / 2.0f;

    // Reset frequency and phase to avoid drifting
    frequency = originalFrequency;
}