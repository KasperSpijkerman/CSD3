#include "phaser.h"

// Constructor
Phaser::Phaser()
        : delayBuffer{CircBuffer(1024), CircBuffer(1024)} // Initializing with a default size (e.g., 1024 samples)
{
    // Reset all filters to their initial state
    for (int ch = 0; ch < 2; ++ch)
    {
        for (int i = 0; i < 5; ++i)
        {
            allPassFilters[ch][i].reset();
        }
    }
}

// Destructor
Phaser::~Phaser() {}

// Prepare the phaser (set sample rate for oscillators, initialize any needed variables)
void Phaser::prepareToPlay(double sampleRate)
{
    this->samplerateFX = sampleRate;

    // Set the sample rate for the LFO oscillators
    for (SineOscillator& oscillator : oscillators)
    {
        oscillator.setSamplerate(samplerateFX);
    }

    // Default dry/wet to 50% wet
    setDryWet(0.5f);
    // Initialize circular buffers for both channels
    for (int i = 0; i < 2; ++i) {
        delayBuffer[i].setSize(static_cast<uint>(sampleRate * maxDelayTime)); // Set up max size based on maxDelayTime
    }
}

// Calculate modulation signal and apply it to the all-pass filters for each channel
void Phaser::calcMod(int channel) {
    // Generate a new sample from the LFO
    oscillators[channel].tick();
    float modulationSignal = (oscillators[channel].getSample() + 1.0f) / 2.0f;

    // Smooth the modulation signal to prevent abrupt changes
    float smoothedModulation = smoothingFunction(modulationSignal);

    // Adjust distance for delayBuffer if needed (if you're using the delay buffer)
    float adjustedDistance = smoothedModulation * maxDelayTime;
    delayBuffer[channel].setDistance(adjustedDistance);

    // Directly set coefficients on each all-pass filter
    for (int i = 0; i < 5; ++i) {
        float g = std::clamp(smoothedModulation * intensity, 0.05f, 0.95f);
        allPassFilters[channel][i].setCoefficient(g);
    }
}


// Process the audio sample (apply phaser effect)
float Phaser::output(float input, int channel)
{
    // Calculate modulation for the current channel
    calcMod(channel);

    // Process the input through the chain of all-pass filters
    float processedSignal = input;

    for (int i = 0; i < 5; ++i)
    {
        processedSignal = allPassFilters[channel][i].process(processedSignal);
    }

    // Ensure dry/wet mix values are valid
    dry = std::clamp(dry, 0.0f, 1.0f);
    wet = std::clamp(wet, 0.0f, 1.0f);

    // Mix processed signal with the original input based on dry/wet values
    float mixedOutput = (input * dry) + (processedSignal * wet);

    // Apply gain compensation if necessary (optional)
    float gainCompensation = 1.0f;  // Adjust as needed to normalize volume
    mixedOutput *= gainCompensation;

    return mixedOutput;
}


// Set the intensity (modulation depth)
void Phaser::setIntensity(float newIntensity)
{
    this->intensity = std::clamp(newIntensity, 0.0f, 1.0f);  // Keep intensity in a safe range
}

// Set the modulation rate (speed of the LFO)
void Phaser::setRate(float newRateL, float newRateR)
{
    oscillators[0].setFrequency(newRateL);
    oscillators[1].setFrequency(newRateR);
}

void Phaser::setDryWet(float mix)
{
    // Ensure the mix value is clamped between 0.0 and 1.0
    dry = std::clamp(1.0f - mix, 0.0f, 1.0f);
    wet = std::clamp(mix, 0.0f, 1.0f);
}

float Phaser::smoothingFunction(float input) {
    static float lastOutput = 0.0f;
    float smoothingAmount = 0.02f; // Adjust this value to control the amount of smoothing
    lastOutput = lastOutput * (1.0f - smoothingAmount) + input * smoothingAmount;
    return lastOutput;
}
