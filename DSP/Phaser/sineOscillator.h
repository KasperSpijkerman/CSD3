#include "oscillator.h"
#include <cmath>

class SineOscillator : public Oscillator {
public:
    SineOscillator(float frequency = 440.0f, float amplitude = 1.0f) : Oscillator(frequency, amplitude) {}

protected:
    // Implementing the pure virtual function 'calculate()'
    // SineOscillator::calculate
    void calculate() override;

private:
    float sample { 0.0f };
};
