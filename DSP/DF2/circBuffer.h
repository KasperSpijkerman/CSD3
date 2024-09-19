#include "Interpolation.cpp"

#pragma once

#pragma once

class CircBuffer {

    using uint = unsigned int;

public:
    CircBuffer(uint size = 256);  // Default size like the other class
    ~CircBuffer();

    // Input/output and incrementing the heads
    void write(float value);  // Change input() to write()
    float read();  // Change output() to read()
    void incrementHeads();

    // Setters
    void setDistance (float distance);
    void setSize(uint size);  // Add setSize() method

protected:
    inline void wrapreadHeader (float& head);
    inline void wrapwriteHeader (uint& head);
    inline void incrementWrite();
    inline void incrementRead();
    void deleteBuffer();

    float* buffer;
    uint currentSize { 0 };
    float distance { 0 };
    uint writeHead { 0 };
    // Float of readhead so it can interpolate
    float readHead { 0 };
};