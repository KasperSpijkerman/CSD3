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
    if (i0 < 0) i0 += currentSize;

    int i1 = (i0 + 1) % currentSize;
    int i2 = (i1 + 1) % currentSize;
    int i3 = (i2 + 1) % currentSize;

    // Fractional part for interpolation
    float t = readHead - floor(readHead);

    // Perform cubic interpolation
    return util.cubicInterpolate(buffer[i0], buffer[i1], buffer[i2], buffer[i3], t);
}

// CircBuffer::setDistance (adjusting to ensure smooth transitions)
void CircBuffer::setDistance(float distance) {
    this->distance = distance;

    // Smoothly adjust the readHead over several samples instead of jumping
    float targetReadHead = writeHead - distance;
    if (targetReadHead < 0) {
        targetReadHead += currentSize;
    }

    // Apply gradual change to readHead
    readHead += (targetReadHead - readHead) * 0.1f; // Smooth transition, tweak smoothing factor
    if (readHead >= currentSize) {
        readHead -= currentSize;
    }
}

// Ensure the `incrementWrite` and `incrementRead` functions increment correctly
inline void CircBuffer::incrementWrite()
{
    writeHead = (writeHead + 1) % currentSize;  // Wrap using modulo
}

inline void CircBuffer::incrementRead()
{
    readHead = fmod(readHead + 1, currentSize);  // Use `fmod` for smooth wrap-around
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
