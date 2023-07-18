set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(step step.cpp)
target_include_directories(step PUBLIC .)
target_link_libraries(step PUBLIC stack_item serializable)