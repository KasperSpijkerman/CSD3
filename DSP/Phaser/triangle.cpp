#include "triangle.h"
#include "math.h"

Triangle::Triangle(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
}

void Triangle::calculate()
{
  sample = (2/M_PI)* asin(sin((2*M_PI*phase)));
}

