cmake_minimum_required(VERSION 3.6)
project(Deque)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp include/deque.h include/deque_iterator.h)
add_executable(Deque ${SOURCE_FILES})