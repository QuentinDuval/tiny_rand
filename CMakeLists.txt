cmake_minimum_required(VERSION 3.6)
project(TinyRandom)

set(CMAKE_CXX_STANDARD 14)

add_library(tiny_rand INTERFACE)
target_include_directories(tiny_rand INTERFACE "include")

add_subdirectory(samples)
add_subdirectory(tests)
