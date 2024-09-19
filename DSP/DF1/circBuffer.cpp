#include "circBuffer.h"
#include <iostream>
#include <cmath>

// Constructor
CircBuffer::CircBuffer(uint size) : buffer(new float[size]), currentSize(size) {}

// Destructor
CircBuffer::~CircBuffer() {
    deleteBuffer();
}

// Writing values to the buffer
void CircBuffer::write(float value) {
    buffer[writeHead] = value;
    incrementWrite();
}

// Reading values from the buffer (including interpolation)
float CircBuffer::read() {
    int i = (int) trunc(readHead);
    float factor = readHead - (float) i;
    float nextSample = buffer[(i + 1) % currentSize];  // Wrap read head for interpolation
    incrementRead();
    return Interpolation::linearInterpolation(factor, buffer[i], nextSample);
}

// Setting a distance between the read and write heads
void CircBuffer::setDistance(float distance) {
    this->distance = distance;
    float readHeadBuffer = writeHead - distance;
    if(readHeadBuffer < 0) {
        readHead = readHeadBuffer + currentSize;
    } else {
        readHead = readHeadBuffer;
    }
}

// Increment write head
inline void CircBuffer::incrementWrite() {
    writeHead++;
    wrapwriteHeader(writeHead);
}

// Increment read head
inline void CircBuffer::incrementRead() {
    readHead++;
    wrapreadHeader(readHead);
}

// Increment both heads
void CircBuffer::incrementHeads() {
    incrementRead();
    incrementWrite();
}

// Deleting the buffer
void CircBuffer::deleteBuffer() {
    delete[] buffer;
}

// Wrapping the read head
inline void CircBuffer::wrapreadHeader(float& head) {
    if (head >= currentSize) {
        head = 0;
    }
}

// Wrapping the write head
inline void CircBuffer::wrapwriteHeader(uint& head) {
    if (head >= currentSize) {
        head = 0;
    }
}

// Set the size of the buffer
void CircBuffer::setSize(uint size) {
    delete[] buffer;  // Free old buffer
    buffer = new float[size];
    currentSize = size;
    std::fill(buffer, buffer + size, 0.0f);  // Initialize the buffer to 0
    writeHead = 0;
    readHead = 0;
}