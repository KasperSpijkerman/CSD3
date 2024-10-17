#include "circBuffer.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>

// Constructor
CircBuffer::CircBuffer(uint size)
        : buffer(nullptr), currentSize(0), writeHead(0), readHead(0), distance(0)
{
    setSize(size);
}

// Destructor
CircBuffer::~CircBuffer()
{
    deleteBuffer();
}

// Dynamically resize the buffer
void CircBuffer::setSize(uint size)
{
    if (size != currentSize) {
        deleteBuffer(); // Clean the old buffer
        currentSize = size;
        buffer = new float[currentSize](); // Initialize new buffer with zero
    }
}

// Input value at writeHead and increment writeHead
void CircBuffer::input(float value)
{
    buffer[writeHead] = value;   // Store the value at the write head
    incrementWrite();            // Increment write head
}

// Output value using cubic interpolation
// Output value using cubic interpolation
float CircBuffer::output()
{
    // Ensure readHead stays within buffer bounds
    int i0 = (int)floor(readHead) - 1;
    int i1 = (i0 + 1) % currentSize;
    int i2 = (i1 + 1) % currentSize;
    int i3 = (i2 + 1) % currentSize;

    // Ensure the indices wrap around the buffer
    if (i0 < 0) i0 += currentSize;

    // Fractional part for interpolation (0 <= t < 1)
    float t = readHead - floor(readHead);

    // Use cubic interpolation for smooth output
    return util.cubicInterpolate(buffer[i0], buffer[i1], buffer[i2], buffer[i3], t);
}

// Set the distance between writeHead and readHead
void CircBuffer::setDistance(float distance)
{
    this->distance = distance;
    float readHeadBuffer = writeHead - distance;

    if (readHeadBuffer < 0) {
        readHead = readHeadBuffer + currentSize;
    } else {
        readHead = fmod(readHeadBuffer, currentSize);
    }
}

// Increment the write head and wrap it
inline void CircBuffer::incrementWrite()
{
    writeHead++;
    wrapWriteHead(writeHead);
}

// Increment the read head and wrap it
inline void CircBuffer::incrementRead()
{
    readHead++;
    wrapReadHead(readHead);
}

// Increment both heads
void CircBuffer::incrementHeads()
{
    incrementRead();
    incrementWrite();
}

// Delete the buffer
void CircBuffer::deleteBuffer()
{
    if (buffer) {
        delete[] buffer;
        buffer = nullptr;
    }
}

// Wrap readHead around to 0 if it exceeds currentSize
inline void CircBuffer::wrapReadHead(float& head)
{
    if (head >= currentSize) {
        head -= currentSize;  // Instead of setting it to 0, subtract currentSize for better continuity
    }
}

// Wrap writeHead around to 0 if it exceeds currentSize
inline void CircBuffer::wrapWriteHead(uint& head)
{
    if (head >= currentSize) {
        head -= currentSize;  // Same approach as with readHead
    }
}
