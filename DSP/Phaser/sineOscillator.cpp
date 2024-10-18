//
// Created by Kasper Spijkerman on 03/10/2024.
//

#include "sineOscillator.h"


void SineOscillator::calculate() {
    sample = amplitude * std::sin(2.0f * M_PI * phase);
    phase += frequency / samplerate;

    // Smooth wrapping
    while (phase >= 1.0f) {
        phase -= 1.0f;
    }
    while (phase < 0.0f) {
        phase += 1.0f;
    }
}