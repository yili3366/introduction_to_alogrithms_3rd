cmake_minimum_required(VERSION 3.5)
project(chap16)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp BTree.h BTree.cpp BTreeTest.cpp)

add_executable(chap16 ${SOURCE_FILES})
target_link_libraries(chap16 gtest.a pthread.so)