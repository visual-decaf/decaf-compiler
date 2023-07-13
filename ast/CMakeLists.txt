set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(ast expr.cpp stmt.cpp)
target_include_directories(ast PUBLIC .)
target_link_libraries(ast PUBLIC parser_impl_basic type serializable)