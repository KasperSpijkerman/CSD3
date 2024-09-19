#pragma once
#include "oscillator.h"

class Triangle : public Oscillator
{
public:
  Triangle(float frequency = 4, float amplitude = 0.5);

protected:
  void calculate();
};
