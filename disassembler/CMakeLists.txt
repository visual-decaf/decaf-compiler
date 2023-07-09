add_library(deassembler disassembler.cpp)
target_include_directories(deassembler PUBLIC .)
target_link_libraries(deassembler PUBLIC byte_code)