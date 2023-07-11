add_library(type type.cpp ../tests/type/type_test.cpp)
target_include_directories(type PUBLIC .)
target_link_libraries(type PUBLIC serializable)