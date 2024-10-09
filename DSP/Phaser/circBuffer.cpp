#include "circBuffer.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>

using namespace std;

// Constructor
CircBuffer::CircBuffer(uint size) : buffer(new float[size]), currentSize(size)
{
    // Initialize the buffer with zero
    memset(buffer, 0, currentSize * sizeof(float));
}

// Destructor
CircBuffer::~CircBuffer()
{
    deleteBuffer();
}

// Input value at writeHead and increment writeHead
void CircBuffer::input(float value)
{
    buffer[writeHead] = value;   // Store the value at the write head
    incrementWrite();            // Increment write head
}

// Reading values and outputting them with cubic interpolation
float CircBuffer::output()
{
    // Use cubic interpolation for smooth output
    int i0 = (int)trunc(readHead) - 1;
    int i1 = (i0 + 1) % currentSize;
    int i2 = (i1 + 1) % currentSize;
    int i3 = (i2 + 1) % currentSize;

    // Ensure the indices wrap around the buffer
    if (i0 < 0) i0 += currentSize;

    // Fractional part for interpolation
    float t = readHead - (float)i1;

    // Perform cubic interpolation
    return util.cubicInterpolate(buffer[i0], buffer[i1], buffer[i2], buffer[i3], t);
}

// Set the distance between writeHead and readHead
void CircBuffer::setDistance (float distance)
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
    wrapwriteHeader(writeHead);
}

// Increment the read head and wrap it
inline void CircBuffer::incrementRead()
{
    readHead++;
    wrapreadHeader(readHead);
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
    delete[] buffer;
}

// Wrap readHead around to 0 if it exceeds currentSize
inline void CircBuffer::wrapreadHeader(float& head)
{
    if (head >= currentSize) {
        head = 0;
    }
}

// Wrap writeHead around to 0 if it exceeds currentSize
inline void CircBuffer::wrapwriteHeader(uint& head)
{
    if (head >= currentSize) {
        head = 0;
    }
}
