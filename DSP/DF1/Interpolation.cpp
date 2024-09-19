#include <iostream>
#include <ostream>

struct Interpolation {
    // nearest neighbor mapping based on Ciska Vriezenga's code
    static float mapNearestNeighbour(float value, float low, float high) {
        if (value >= 0.0f && value <= 1.0f) {
            if (value < 0.5f) {
                return low;
            } else {
                return high;
            }
        } else {
            std::cout << " ERROR: must be a float between [0,1]" << std::endl;
            return 0;
        }
    }

    // calculates a value in a new range old a given value and a range
    // made in a lecture from Ciska Vriezenga
    static float mapInRange(float value, float oldLow, float oldHigh,
                            float newLow, float newHigh) {
        float delta = value - oldLow;
        float oldRange = oldHigh - oldLow;
        float percentage = delta / oldRange;
        float newRange = newHigh - newLow;
        return ((percentage * newRange) + newLow);
    }

    // returns the interpolation between 2 values where (float)value is a point in
    // the closed unit interval [0, 1]
    //    based on a linear interpolation found on
    //    https://paulbourke.net/miscellaneous/interpolation/
    static float linearInterpolation(float value, float point1, float point2) {

        return (point1 * (1.0f - value) + point2 * value);
    }

    // returns the interpolation between 2 values with a cosinic "smoothing"
    // where (float)value is a point in the closed unit interval [0, 1]
    //   based on a cosine interpolation found on
    //   https://paulbourke.net/miscellaneous/interpolation/
    static float cosineInterpolation(float value, float point1, float point2) {

        float cosineValue = (1 - cos(value * (4 * atan(1)))) / 2;
        return (point1 * (1 - cosineValue) + point2 * cosineValue);
    }

    // returns te interpolation with more continuity than cosinic. point1 to
    // point2 is still the range but uses point0 as the point before point1 and
    // point3 as the point after point2.
    //    based on a cubic interpolation found on
    //    https://paulbourke.net/miscellaneous/interpolation/
    static float cubicInterpolation(float value, float point0, float point1,
                                    float point2, float point3) {
        float valueSquare = value * value;
        float valuePow3 = valueSquare * value;
        float a0 = point3 - point2 - point0 + point1;
        float a1 = point0 - point1 - a0;
        float a2 = point2 - point0;
        return (a0 * valuePow3 + a1 * valueSquare + a2 * value + point1);
    }
};