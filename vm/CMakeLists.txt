add_library(vm vm.cpp)
target_include_directories(vm PUBLIC .)
target_link_libraries(vm PUBLIC byte_code compiler)