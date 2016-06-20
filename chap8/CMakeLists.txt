cmake_minimum_required(VERSION 3.5)
project(chap8)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp CountingSort.h CountingSort.cpp CountingSortTest.cpp BucketSort.h BucketSort.cpp BucketSortTest.cpp)

add_executable(chap8 ${SOURCE_FILES})
target_link_libraries(chap8 gtest.a pthread.so)