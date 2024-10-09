#pragma once

struct Util
{
    static float cubicInterpolate(float v0, float v1, float v2, float v3, float t);
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

float Util::cubicInterpolate(float v0, float v1, float v2, float v3, float t)
{
    float a0 = v3 - v2 - v0 + v1;
    float a1 = v0 - v1 - a0;
    float a2 = v2 - v0;
    float a3 = v1;

    return a0 * (t * t * t) + a1 * (t * t) + a2 * t + a3;
}