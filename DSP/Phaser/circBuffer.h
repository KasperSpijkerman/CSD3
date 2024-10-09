#pragma once
#include "effect.h"
#include "utilities.h"

class CircBuffer {

    using uint = unsigned int;

public:
    // Constructor and Destructor
    CircBuffer(uint size);
    ~CircBuffer();

    // Input/output and incrementing the heads
    void input(float value);
    float output();  // This will now use cubic interpolation
    void incrementHeads();

    // Setters
    void setDistance(float distance);
    void setSize(uint size);

protected:
    // Wrapping and incrementing heads
    inline void wrapreadHeader(float& head);
    inline void wrapwriteHeader(uint& head);
    inline void incrementWrite();
    inline void incrementRead();
    void deleteBuffer();

    // Buffer pointer
    float* buffer { nullptr };

    // Utility for interpolation
    Util util;

    // Current buffer size
    uint currentSize { 0 };

    // Distance determines delay time later on
    float distance { 0 };

    // Write and read heads
    uint writeHead { 0 };
    float readHead { 0 };  // Float to allow interpolation
};