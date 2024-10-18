#include "AllPassFilter.h"

// Constructor to initialize the all-pass filter with default values
AllPassFilter::AllPassFilter()
        : g(0.0f), prevInput(0.0f), prevOutput(0.0f)
{
}

void AllPassFilter::setCoefficient(float newG)
{
    ensureValidCoefficient(newG);

    // Improved smoothing for coefficient changes using exponential smoothing
    float smoothingFactor = 0.03f;  // Increase this value for smoother transitions
    g += (newG - g) * smoothingFactor;
}

// Process a single sample through the all-pass filter
float AllPassFilter::process(float input)
{
    // Apply the all-pass filter formula: y(n) = -g * x(n) + x(n-1) + g * y(n-1)
    float output = (-g * input) + prevInput + (g * prevOutput);

    // Update the previous input and output for the next iteration
    prevInput = input;
    prevOutput = output;

    return output;
}

// Reset the filter (clear internal buffers)
void AllPassFilter::reset()
{
    prevInput = 0.0f;
    prevOutput = 0.0f;
}

// Ensure that 'g' is in the range [0.01, 0.99]
void AllPassFilter::ensureValidCoefficient(float& gValue)
{
    if (gValue < 0.01f)
        gValue = 0.01f;
    else if (gValue > 0.99f)
        gValue = 0.99f;
}
