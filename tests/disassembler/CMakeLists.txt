add_executable(disassembler_test disassembler_test.cpp)
target_link_libraries(disassembler_test PRIVATE
        disassembler byte_code
        Catch2::Catch2WithMain)
catch_discover_tests(disassembler_test)
