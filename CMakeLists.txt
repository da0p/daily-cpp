cmake_minimum_required(VERSION 3.21)
project(DailyCpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_subdirectory(algorithm)
add_subdirectory(ccwcpp)
add_subdirectory(functional)
add_subdirectory(lambda)
add_subdirectory(misc)
add_subdirectory(range)
add_subdirectory(string)
