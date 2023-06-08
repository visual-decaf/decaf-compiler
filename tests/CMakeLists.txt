add_executable(test_add test_add.cpp)

target_link_libraries(test_add PRIVATE add_lib sub_lib fac_lib Catch2::Catch2WithMain)
catch_discover_tests(test_add)