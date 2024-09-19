#pragma once

struct Util
{
    float mapInRange(float factor, float inputMin, float inputMax, float outputMin, float outputMax)
    {
        float inputDelta = inputMax - inputMin;
        float outputDelta = outputMax - outputMin;
        float valueScaled = (factor-inputMin)/inputDelta;
        float output = valueScaled * outputDelta + outputMin;
        return output;
    }

    float linearMap(float factor, float min, float max)
    {
        float output = mapInRange(factor, 0.0, 1.0, min, max);
        return output;
    }

};