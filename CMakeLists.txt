cmake_minimum_required(VERSION 3.24)
project(decaf_compiler VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 23)

find_package(FLEX)
find_package(BISON)

BISON_TARGET(DecafParser parser/parser_impl.yy ${CMAKE_CURRENT_BINARY_DIR}/parser_impl.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser_impl.h
)
FLEX_TARGET(DecafScanner scanner/scanner_impl.l ${CMAKE_CURRENT_BINARY_DIR}/scanner_impl.cpp)
add_executable(simple_test tests/simple_driver.cpp
    ${FLEX_DecafScanner_OUTPUTS}
    ${BISON_DecafParser_OUTPUT_SOURCE}
)
target_include_directories(simple_test
    PRIVATE ${CMAKE_BINARY_DIR}
)

add_subdirectory(tests)