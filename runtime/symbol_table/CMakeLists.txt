set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(symbol_table symbol_table.cpp)
target_include_directories(symbol_table PUBLIC .)
target_link_libraries(symbol_table PUBLIC stack_item serializable)
