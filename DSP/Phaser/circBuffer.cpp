#include "circBuffer.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>

// short 
using namespace std;

// Constructor
CircBuffer::CircBuffer(uint size) : buffer(new float[size]), currentSize(size)
{
    // Initialize the buffer with zero
    memset(buffer, 0, currentSize * sizeof(float));  // Fixed the usage of currentSize instead of bufferSize
}

// Destructor
CircBuffer::~CircBuffer()
{
    deleteBuffer();  // Clean up the buffer memory
}

// Input value at writeHead and increment writeHead
void CircBuffer::input(float value)
{
    buffer[writeHead] = value;   // Store the value at the write head
    incrementWrite();            // Increment write head
}

// Reading values and outputting them with interpolation
float CircBuffer::output()
{
    // Linear interpolation
    int i = (int)trunc(readHead);
    int iNext = (i + 1) % currentSize;  // Ensure i + 1 wraps around the buffer correctly

    // Interpolate between two adjacent buffer values
    float factor = readHead - (float)i;
    return util.linearMap(factor, buffer[i], buffer[iNext]);  // Safe access of buffer[iNext]
}

// Set the distance between writeHead and readHead
void CircBuffer::setDistance (float distance)
{
    this->distance = distance;
    float readHeadBuffer = writeHead - distance;

    if (readHeadBuffer < 0) {
        readHead = readHeadBuffer + currentSize;
    } else {
        readHead = fmod(readHeadBuffer, currentSize);  // Use fmod for safer wrapping
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
