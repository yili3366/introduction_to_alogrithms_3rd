cmake_minimum_required(VERSION 3.6)
project(chap25)

include_directories("/home/usr/include")
link_directories("/home/usr/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    Main.cpp GraphMatrix.h GraphMatrix.cpp GraphAdjacencyList.h GraphTest.cpp GraphAdjacencyListTest.cpp)
#set(JOHNSON_SOURCE_FILES )

add_executable(chap25 ${SOURCE_FILES})
#add_executable(johnson)
target_link_libraries(chap25 gtest.a pthread.so)
