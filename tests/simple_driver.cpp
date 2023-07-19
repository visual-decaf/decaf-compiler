#include "visual_decaf.h"
#include <iostream>
int main() {
    int id = get_id();
    upload_code("int x;", id);
    char* tokens = get_token_stream(id);
    std::cout << tokens << std::endl;
    free(tokens);
    char* ast = get_ast(id);
    std::cout << ast << std::endl;
}