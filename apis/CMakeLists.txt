set(Boost_NO_WARN_NEW_VERSIONS ON)
find_package(Boost REQUIRED
        COMPONENTS json
        )

add_library(serializable INTERFACE serializable.h)
target_include_directories(serializable INTERFACE . ${Boost_INCLUDE_DIRS})
target_link_libraries(serializable INTERFACE ${Boost_LIBRARIES})