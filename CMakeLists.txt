cmake_minimum_required(VERSION 3.24)
project(decaf_compiler VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

find_package(FLEX)
find_package(BISON)
include_directories(${FLEX_INCLUDE_DIR})

BISON_TARGET(DecafParser parser/parser_impl.yy ${CMAKE_BINARY_DIR}/parser_impl.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser_impl.h
        )
FLEX_TARGET(DecafScanner scanner/scanner_impl.l ${CMAKE_BINARY_DIR}/scanner_impl.cpp)
ADD_FLEX_BISON_DEPENDENCY(DecafScanner DecafParser)
add_custom_target(run_flex_bison
        DEPENDS ${CMAKE_BINARY_DIR}/parser_impl.cpp ${CMAKE_BINARY_DIR}/scanner_impl.cpp
        )

include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(token)
add_subdirectory(scanner)

find_package(Catch2 3 REQUIRED)
include(CTest)
include(Catch)

add_subdirectory(tests)
add_subdirectory(apis)