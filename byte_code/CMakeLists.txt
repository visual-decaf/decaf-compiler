add_library(byte_code byte_code.cpp byte_code_visitor.cpp byte_code_driver.cpp)
target_include_directories(byte_code PUBLIC .)