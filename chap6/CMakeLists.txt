cmake_minimum_required(VERSION 3.5)
project(chap6)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp HeapSort.cpp HeapSort.h HeapSortTest.cpp PriorityQueue.h PriorityQueue.cpp PriorityQueueTest.cpp)

add_executable(chap6 ${SOURCE_FILES})
target_link_libraries(chap6 gtest.a pthread.so)