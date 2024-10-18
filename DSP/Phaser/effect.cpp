#include "effect.h"


void Effect::setDryWet(float wetInput)
{
    // Clamp the input to the range [0, 1]
    wetInput = std::clamp(wetInput, 0.0f, 1.0f);

    // Set wet and complementary dry values
    wet = wetInput;
    dry = 1.0f - wetInput;
}