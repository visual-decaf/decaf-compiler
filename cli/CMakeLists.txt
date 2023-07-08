add_executable(decaf_cli decaf.cpp)
target_link_libraries(decaf_cli
        PRIVATE scanner parser compiler vm
        )