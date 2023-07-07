add_library(token token.cpp)
target_include_directories(token PUBLIC .)
target_link_libraries(token PUBLIC parser_impl_basic)
add_dependencies(token run_flex_bison)