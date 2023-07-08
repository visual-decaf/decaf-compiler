add_subdirectory(scanner)
add_subdirectory(parser)
add_subdirectory(compiler)
add_subdirectory(vm)

add_executable(simple_driver simple_driver.cpp)
target_link_libraries(simple_driver PUBLIC token scanner)