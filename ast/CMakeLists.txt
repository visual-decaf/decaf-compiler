add_library(ast expr.cpp)
target_include_directories(ast PUBLIC .)
target_link_libraries(ast PUBLIC token)