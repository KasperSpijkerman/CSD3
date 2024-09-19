cmake_minimum_required(VERSION 3.24)
project(DF1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DF1 main.cpp circBuffer.cpp Interpolation.cpp)