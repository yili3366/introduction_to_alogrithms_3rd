cmake_minimum_required(VERSION 3.6)
project(chap26)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    GraphAdjacencyList.h
    Main.cpp GraphAdjacenyListTest.cpp)

add_executable(chap26 ${SOURCE_FILES})
target_link_libraries(chap26 gtest.a pthread.so)