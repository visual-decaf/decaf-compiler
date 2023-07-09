add_executable(ast_test ast_test.cpp)
target_link_libraries(ast_test PRIVATE ast Catch2::Catch2WithMain)
catch_discover_tests(ast_test)
