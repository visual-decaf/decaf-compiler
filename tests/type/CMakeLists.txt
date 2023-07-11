add_executable(type_test type_test.cpp)
target_link_libraries(type_test PRIVATE type Catch2::Catch2WithMain)
catch_discover_tests(type_test)