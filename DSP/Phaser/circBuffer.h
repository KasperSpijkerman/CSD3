#include "effect.h"
#include "utilities.h"

#pragma once

class CircBuffer {

    using uint = unsigned int;

public:
    CircBuffer(uint size);
    ~CircBuffer(); 
    
    // input/output and incrementing the heads
    void input (float value);
    float output(); 
    void incrementHeads(); 

    // setters
    void setDistance (float distance);
    void setSize(uint size);


protected:
    // wrapping and incrementing heads
    inline void wrapreadHeader (float& head);
    inline void wrapwriteHeader (uint& head);
    inline void incrementWrite();
    inline void incrementRead(); 
    void deleteBuffer();

    // buffer pointer
    float* buffer;
    // utility for interpolating
    Util util;
    uint currentSize { 0 };
    // distance determines the delay time later on
    float distance { 0 };
    uint writeHead { 0 };
    // float of readhead so it can interpolate
    float readHead { 0 };
};