add_executable(vm_test vm_test.cpp)
target_link_libraries(vm_test PRIVATE vm Catch2::Catch2WithMain)
catch_discover_tests(vm_test)