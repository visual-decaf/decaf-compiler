add_library(parser_impl_basic INTERFACE
        ast_basic.h parser_basic.h
        )
target_include_directories(parser_impl_basic INTERFACE .)