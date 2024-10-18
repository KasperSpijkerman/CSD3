#include "sineOscillator.h"

SineOscillator::SineOscillator(float frequency, float amplitude, float samplerate)
        : frequency(frequency), amplitude(amplitude), samplerate(samplerate) {}

// Set the frequency
void SineOscillator::setFrequency(float newFrequency) {
    frequency = newFrequency;
}

// Set the amplitude
void SineOscillator::setAmplitude(float newAmplitude) {
    amplitude = newAmplitude;
}

// Set the samplerate
void SineOscillator::setSamplerate(float newSamplerate) {
    samplerate = newSamplerate;
}

// Get the current sample
float SineOscillator::getSample() {
    return sample;
}

// Update the oscillator's state, increment the phase and calculate the next sample
void SineOscillator::tick() {
    calculate();
    phase += frequency / samplerate;

    // Smooth wrapping
    while (phase >= 1.0f) {
        phase -= 1.0f;
    }
    while (phase < 0.0f) {
        phase += 1.0f;
    }
}

// Calculate the current sample based on the sine wave formula
void SineOscillator::calculate() {
    sample = amplitude * std::sin(2.0f * M_PI * phase);
}
