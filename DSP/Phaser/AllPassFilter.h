#pragma once

class AllPassFilter
{
public:
    // Constructor
    AllPassFilter();

    // Sets the 'g' coefficient, which modulates the all-pass filter's response
    void setCoefficient(float newG);

    // Process a single audio sample through the all-pass filter
    float process(float input);

    // Reset the filter state (clear the internal buffers)
    void reset();

private:
    float g;           // Coefficient for the all-pass filter
    float prevInput;    // Previous input sample
    float prevOutput;   // Previous output sample
};
