#include "Phaser.h"
#include <algorithm>
#include <cmath>

// Constructor
Phaser::Phaser() {
    // Initialize all filters to their reset state
    for (int ch = 0; ch < 2; ++ch) {
        for (int i = 0; i < 5; ++i) {
            allPassFilters[ch][i].reset();
        }
    }
}

// Destructor
Phaser::~Phaser() {}

// Prepare the phaser (set sample rate for oscillators, initialize any needed variables)
void Phaser::prepareToPlay(double sampleRate) {
    this->sampleRate = sampleRate;

    // Set the sample rate for the LFO oscillators
    for (SineOscillator& oscillator : oscillators) {
        oscillator.setSamplerate(sampleRate);
    }

    // Default dry/wet mix
    setDryWet(0.5f);
}

// Update the LFOs and set the all-pass filter coefficients
void Phaser::updateLFO(int channel) {
    oscillators[channel].tick();
    float modulationSignal = (oscillators[channel].getSample() + 1.0f) / 2.0f;

    // Smooth the modulation signal to avoid abrupt changes
    float smoothedModulation = smoothingFunction(modulationSignal);

    // Set coefficients on each all-pass filter based on modulation
    for (int i = 0; i < 5; ++i) {
        float g = std::clamp(smoothedModulation * intensity, 0.05f, 0.95f);
        allPassFilters[channel][i].setCoefficient(g);
    }
}

// Process the audio sample (apply phaser effect)
float Phaser::output(float input, int channel) {
    // Update LFO for the current channel
    updateLFO(channel);

    // Pass the input through the all-pass filters
    float processedSignal = input;
    for (int i = 0; i < 5; ++i) {
        processedSignal = allPassFilters[channel][i].process(processedSignal);
    }

    // Mix processed signal with the original input based on dry/wet values
    float mixedOutput = (input * dry) + (processedSignal * wet);

    return mixedOutput;
}

// Set the intensity (modulation depth)
void Phaser::setIntensity(float newIntensity) {
    this->intensity = std::clamp(newIntensity, 0.0f, 1.0f);  // Keep intensity in a safe range
}

// Set the modulation rate (speed of the LFO)
void Phaser::setRate(float newRateL, float newRateR) {
    oscillators[0].setFrequency(newRateL);
    oscillators[1].setFrequency(newRateR);
}

// Set the dry/wet mix
void Phaser::setDryWet(float mix) {
    // Ensure the mix value is clamped between 0.0 and 1.0
    dry = std::clamp(1.0f - mix, 0.0f, 1.0f);
    wet = std::clamp(mix, 0.0f, 1.0f);
}

// Simple smoothing function using exponential smoothing
float Phaser::smoothingFunction(float input) {
    static float lastOutput = 0.0f;
    float smoothingAmount = 0.02f; // Adjust this value to control the amount of smoothing
    lastOutput = lastOutput * (1.0f - smoothingAmount) + input * smoothingAmount;
    return lastOutput;
}
