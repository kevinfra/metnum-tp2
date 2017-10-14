cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -pthread")

add_executable(crossval crossval.cpp)
target_link_libraries (crossval metnum-tp2-base)
