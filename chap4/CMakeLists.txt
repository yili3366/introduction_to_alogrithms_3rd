cmake_minimum_required(VERSION 3.5)
project(chap4)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath=/home/usr/lib/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        FindMaximumSubarray.cpp Main.cpp FindMaximumSubarray.h FindMaximumSubarrayTest.cpp StrassenMatrixMultiply.h StrassenMatrixMultiply.cpp StrassenMatrixMultiplyTest.cpp)

add_executable(chap4 ${SOURCE_FILES})
target_link_libraries(chap4 gtest.a pthread.so)
