set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(parser parser.cpp
        ${BISON_DecafParser_OUTPUTS}
        )
add_dependencies(parser run_flex_bison)
target_link_libraries(parser PUBLIC ast scanner)
target_include_directories(parser PUBLIC .)