cmake_minimum_required(VERSION 3.6)
project(chap31)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp NumericTheoretic.h NumericTheoretic.cpp NumericTheoreticTest.cpp)

add_executable(chap31 ${SOURCE_FILES})
target_link_libraries(chap31 gtest.a pthread.so)