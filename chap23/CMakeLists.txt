cmake_minimum_required(VERSION 3.5)
project(chap23)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O1")

set(SOURCE_FILES
        Graph.h
        GraphTest.cpp
        Main.cpp)

add_executable(chap23 ${SOURCE_FILES})
target_link_libraries(chap23 gtest.a pthread.so)