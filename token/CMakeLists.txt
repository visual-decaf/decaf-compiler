set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(token token.cpp token_stream.cpp)
target_include_directories(token PUBLIC .)
target_link_libraries(token
        PUBLIC parser_impl_basic serializable)
add_dependencies(token run_flex_bison)