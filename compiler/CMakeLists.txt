set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(compiler compiler.cpp)
target_link_libraries(compiler byte_code ast program type)
target_include_directories(compiler PUBLIC .)