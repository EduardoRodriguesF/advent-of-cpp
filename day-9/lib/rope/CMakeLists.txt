cmake_minimum_required(VERSION 3.26)

project(rope LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(rope rope.cpp)
target_link_libraries(rope coords)
