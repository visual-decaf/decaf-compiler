set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(type type.cpp)
target_include_directories(type PUBLIC .)
target_link_libraries(type PUBLIC serializable)