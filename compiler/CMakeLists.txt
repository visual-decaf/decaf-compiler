add_library(compiler compiler.cpp)
target_link_libraries(compiler byte_code ast program)
target_include_directories(compiler PUBLIC .)