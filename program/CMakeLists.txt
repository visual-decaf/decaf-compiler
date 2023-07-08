add_library(program program.cpp)
target_include_directories(program PUBLIC .)
target_link_libraries(program PUBLIC byte_code)