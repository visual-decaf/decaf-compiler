set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(stack_item
        stack_item.cpp
        bool_stack_item.cpp
        int_stack_item.cpp
        float_stack_item.cpp
        lvalue_stack_item.cpp
        string_stack_item.cpp)
target_include_directories(stack_item PUBLIC .)
target_link_libraries(stack_item PUBLIC type serializable)