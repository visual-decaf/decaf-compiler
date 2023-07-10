add_library(serializable INTERFACE serializable.h)
target_include_directories(serializable INTERFACE .)
target_link_libraries(serializable INTERFACE Boost::json)