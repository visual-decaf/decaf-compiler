add_library(stack stack.cpp)
target_include_directories(stack PUBLIC .)
target_link_libraries(stack PUBLIC stack_item)