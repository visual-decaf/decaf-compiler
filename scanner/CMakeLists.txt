set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(scanner scanner.cpp
        ${FLEX_DecafScanner_OUTPUTS}
        )
target_include_directories(scanner PUBLIC .)
target_link_libraries(scanner PUBLIC token)
add_dependencies(scanner run_flex_bison)