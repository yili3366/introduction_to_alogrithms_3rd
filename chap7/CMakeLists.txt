cmake_minimum_required(VERSION 3.5)
project(chap7)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Main.cpp QuickSort.h QuickSort.cpp QuickSortTest.cpp)

add_executable(chap7 ${SOURCE_FILES})
target_link_libraries(chap7 gtest.a pthread.so)