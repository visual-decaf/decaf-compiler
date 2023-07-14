cmake_minimum_required(VERSION 3.24)
project(decaf_compiler VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

configure_file(meta/version.h.in ${CMAKE_BINARY_DIR}/version.h)

find_package(FLEX)
find_package(BISON)
include_directories(${FLEX_INCLUDE_DIR})

set(Boost_NO_WARN_NEW_VERSIONS ON)
find_package(Boost REQUIRED
        COMPONENTS json log
        )

BISON_TARGET(DecafParser parser/parser_impl.yy ${CMAKE_BINARY_DIR}/parser_impl.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser_impl.h
        )
FLEX_TARGET(DecafScanner scanner/scanner_impl.l ${CMAKE_BINARY_DIR}/scanner_impl.cpp)
ADD_FLEX_BISON_DEPENDENCY(DecafScanner DecafParser)
add_custom_target(run_flex_bison
        DEPENDS ${CMAKE_BINARY_DIR}/parser_impl.cpp ${CMAKE_BINARY_DIR}/scanner_impl.cpp
        )

include_directories(${CMAKE_BINARY_DIR})
add_subdirectory(basic)

add_subdirectory(token)
add_subdirectory(type)
add_subdirectory(ast)
add_subdirectory(scanner)
add_subdirectory(parser)
add_subdirectory(byte_code)
add_subdirectory(program)
add_subdirectory(compiler)
add_subdirectory(runtime)
add_subdirectory(vm)

find_package(Catch2 3 REQUIRED)
include(CTest)
include(Catch)

add_subdirectory(tests)
add_subdirectory(apis)
add_subdirectory(cli)

add_custom_target(graphviz
        COMMAND ${CMAKE_COMMAND} "--graphviz=dependency.dot" .
        COMMAND dot -Tpng dependency.dot -o dependency.png
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        )

add_custom_target(parser_impl_graph
        COMMAND ${BISON_EXECUTABLE} "--graph=parser_impl_graph.dot" ${CMAKE_SOURCE_DIR}/parser/parser_impl.yy
        COMMAND dot -Tpng parser_impl_graph.dot -o parser_impl_graph.png
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")