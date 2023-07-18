set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(compiler compiler.cpp)
target_link_libraries(compiler PUBLIC byte_code ast program type symbol_table)
target_include_directories(compiler PUBLIC .)