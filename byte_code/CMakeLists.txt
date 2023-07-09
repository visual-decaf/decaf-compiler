add_library(byte_code_visitor INTERFACE byte_code_visitor.h)
target_include_directories(byte_code_visitor INTERFACE .)
add_subdirectory(disassembler)

add_library(byte_code byte_code.cpp byte_code_driver.cpp)
target_include_directories(byte_code PUBLIC .)
target_link_libraries(byte_code PUBLIC disassembler)
