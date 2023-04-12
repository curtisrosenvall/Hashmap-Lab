cmake_minimum_required(VERSION 3.15)
project(hashmap_lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(scratch scratch.cpp Hashmap.cpp)

add_executable(tests tests.cpp)
