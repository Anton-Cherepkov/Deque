cmake_minimum_required(VERSION 3.6)
project(Deque)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(include/gtest)
include_directories(include/gtest/googletest/include)
include_directories(include/gtest/googlemock/include)

set(SOURCE_FILES main.cpp include/deque.h include/deque_iterator.h include/test.cpp)
add_executable(Deque ${SOURCE_FILES})
target_link_libraries(Deque gtest gtest_main)