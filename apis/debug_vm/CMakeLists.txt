add_subdirectory(step)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(debug_vm debug_vm.cpp)
target_include_directories(debug_vm PUBLIC .)
target_link_libraries(debug_vm PUBLIC vm)