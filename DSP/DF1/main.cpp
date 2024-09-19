#include "circBuffer.h"
#include <iostream>

CircBuffer buffer;
float sample;

int main() {
    buffer.setSize(8);
    buffer.setDistance(8);
// for loop for 25 points
    for (int i = 0; i < 25; i++) {
        if (i == 0) {
            sample = 1;
        } else {
            sample = 0;
        }
        float buffer1out = buffer.read();
        // formula
        float output =
                (((buffer1out * 0.1678) + sample) * 0.1678) + (buffer1out * -1);
        buffer.write((buffer1out * 0.1678) + sample);
        std::cout << i << ": " << output << std::endl;
    }
    return 0;
}