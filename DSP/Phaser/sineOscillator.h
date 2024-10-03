#include "oscillator.h"
#include <cmath>

class SineOscillator : public Oscillator {
public:
    SineOscillator(float frequency = 440.0f, float amplitude = 1.0f) : Oscillator(frequency, amplitude) {}

protected:
    // Implementing the pure virtual function 'calculate()'
    void calculate() override {
        // A basic sine wave formula
        sample = amplitude * std::sin(2.0f * M_PI * phase);

        // Increment the phase, wrap-around at 1.0
        phase += frequency / samplerate;
        if (phase >= 1.0f) {
            phase -= 1.0f;
        }
    }

private:
    float sample { 0.0f };
};
