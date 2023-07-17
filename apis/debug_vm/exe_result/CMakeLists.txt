set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(exe_result exe_result.cpp)
target_include_directories(exe_result PUBLIC .)
target_link_libraries(exe_result PUBLIC step symbol_table serializable)