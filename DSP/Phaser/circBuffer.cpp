#include "circBuffer.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>

// short 
using namespace std;

CircBuffer::CircBuffer(uint size) : buffer(new float[size]), currentSize(size)
{
    // setting all values to zero in the buffer.
    memset(buffer, 0, sizeof(buffer));
}

CircBuffer::~CircBuffer()
{
    deleteBuffer();
}

// writing values according to list with values
void CircBuffer::input(float value)
{  
    buffer[writeHead] = value;   
}

// reading values and outputting them according to readhead, interpolating the output for no clicks
float CircBuffer::output() 
{
    // Interpolating output
    int i = (int) trunc (readHead);
    float factor = readHead - (float) i;
    return util.linearMap(factor, buffer[i], buffer[i + 1]);
}

// setting a distance between readheader and writeheader
void CircBuffer::setDistance (float distance)
{
    
    this->distance = distance;
    float readHeadBuffer = writeHead - distance;
    if(readHeadBuffer < 0) {
        readHead = readHeadBuffer + currentSize;
    }
    else if(readHeadBuffer > currentSize)
    {
        readHead = readHeadBuffer - currentSize;
    }
     else {
        readHead = readHeadBuffer;
    }
    
}
// incrementing the writehead 
inline void CircBuffer::incrementWrite()
{
    writeHead++;
    wrapwriteHeader(writeHead);
}
// incrementing the readhead
inline void CircBuffer::incrementRead()
{
    readHead++;
    wrapreadHeader(readHead);
}
// incrementing both heads
void CircBuffer::incrementHeads() 
{
    incrementRead();
    incrementWrite();
}
// deleting buffer 
void CircBuffer::deleteBuffer()
{
    delete[] buffer;
}
// starting at zero again, float
inline void CircBuffer::wrapreadHeader(float& head)
{
     if (head >= currentSize)
        {
            head = 0 ;
        }
}
// starting at zero again for writheader, int instead of float
inline void CircBuffer::wrapwriteHeader(uint& head)
{
    if (head >= currentSize)
    {
        head = 0 ;
    }
}

