add_library(program program.cpp constant_pool.cpp)
target_include_directories(program PUBLIC .)
target_link_libraries(program PUBLIC byte_code)