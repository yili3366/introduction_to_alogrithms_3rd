cmake_minimum_required(VERSION 3.5)
project(chap15)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp RodCut.h RodCut.cpp RodCutTest.cpp MatrixChainMultiply.h MatrixChainMultiply.cpp MatrixChainMultiplyTest.cpp Lcs.h Lcs.cpp LcsTest.cpp OptimalBinarySearchTree.h OptimalBinarySearchTree.cpp OptimalBinarySearchTreeTest.cpp)

add_executable(chap15 ${SOURCE_FILES})
target_link_libraries(chap15 gtest.a pthread.so)