add_library(token token.cpp token_stream.cpp)
target_include_directories(token PUBLIC .)
add_dependencies(token run_flex_bison)
target_link_libraries(token PUBLIC serializable)