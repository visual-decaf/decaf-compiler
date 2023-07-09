add_executable(token_test token_test.cpp)
target_link_libraries(token_test PRIVATE token Catch2::Catch2WithMain)
catch_discover_tests(token_test)