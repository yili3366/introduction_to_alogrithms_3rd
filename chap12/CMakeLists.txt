cmake_minimum_required(VERSION 3.5)
project(chap12)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp BinarySearchTree.h BinarySearchTree.cpp BinarySearchTreeTest.cpp)

add_executable(chap12 ${SOURCE_FILES})
target_link_libraries(chap12 gtest.a pthread.so)