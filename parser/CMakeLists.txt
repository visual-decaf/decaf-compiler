add_library(parser parser.cpp)
add_dependencies(parser run_flex_bison)
target_link_libraries(parser PUBLIC ast scanner)