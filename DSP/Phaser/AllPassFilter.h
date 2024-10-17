#pragma once
#include <iostream>

class AllPassFilter
{
public:
    // Constructor
    AllPassFilter();

    // Set the coefficient 'g', ensuring it stays in a valid range
    void setCoefficient(float newG);

    // Process a single audio sample through the all-pass filter
    float process(float input);

    // Reset the filter state (clear the internal buffers)
    void reset();

private:
    // Manually enforce range without std::clamp or juce::jlimit
    void ensureValidCoefficient(float& gValue);

    float g { 0.0f };        // Coefficient for the all-pass filter
    float prevInput { 0.0f };  // Previous input sample
    float prevOutput { 0.0f }; // Previous output sample
};
