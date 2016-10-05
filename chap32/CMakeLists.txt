cmake_minimum_required(VERSION 3.6)
project(chap32)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Main.cpp StringMatching.h StringMatching.cpp StringMatchingTest.cpp)

add_executable(chap32 ${SOURCE_FILES})
target_link_libraries(chap32 gtest.a pthread.so)
