add_library(compiler compiler.cpp program.cpp)
target_link_libraries(compiler byte_code ast)
target_include_directories(compiler PUBLIC .)