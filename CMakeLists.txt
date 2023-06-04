cmake_minimum_required(VERSION 3.24)
project(decaf_compiler VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(add_lib)

find_package(Catch2 3 REQUIRED)
include(CTest)
include(Catch)
add_subdirectory(tests)