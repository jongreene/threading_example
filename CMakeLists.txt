cmake_minimum_required(VERSION 3.8)
project(threading_example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp LockGuard.h)
add_executable(threading_example ${SOURCE_FILES})