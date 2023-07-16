add_subdirectory(stream_scanner)
add_subdirectory(debug_vm)

add_library(serializable INTERFACE serializable.h)
target_include_directories(serializable INTERFACE .)
target_link_libraries(serializable INTERFACE Boost::json)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(visual_decaf SHARED visual_decaf.cpp)
target_include_directories(visual_decaf PUBLIC .)
target_link_libraries(visual_decaf PRIVATE stream_scanner parser compiler vm Boost::json)