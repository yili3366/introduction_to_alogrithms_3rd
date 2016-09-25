cmake_minimum_required(VERSION 3.6)
project(chap30)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp FFT.h)

add_executable(chap30 ${SOURCE_FILES})
target_link_libraries(chap30 gtest.a pthread.so)