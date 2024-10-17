#include "effect.h"


void Effect::setDryWet(float wetInput)
{
    // Use a clamping function (if using JUCE, this would be juce::jlimit)
    wetInput = std::clamp(wetInput, 0.0f, 1.0f);  // Ensure it's within 0-1 range

    // Smoothing for better transitions to avoid clicks (can also be done with a smoothing filter)
    float smoothingFactor = 0.005f;  // Adjust this value to make transitions smoother
    wet = wet * (1.0f - smoothingFactor) + wetInput * smoothingFactor;
    dry = 1.0f - wet;
}