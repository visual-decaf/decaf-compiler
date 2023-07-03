add_library(token token.cpp)
target_include_directories(token PUBLIC .)
add_dependencies(token run_flex_bison)