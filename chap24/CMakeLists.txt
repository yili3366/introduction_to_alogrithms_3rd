cmake_minimum_required(VERSION 3.6)
project(chap24)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        Graph.h
        GraphTest.cpp
        Main.cpp)

add_executable(chap24 ${SOURCE_FILES})
target_link_libraries(chap24 gtest.a pthread.so)