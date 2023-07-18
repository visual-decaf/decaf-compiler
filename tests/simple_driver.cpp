#include "byte_code.h"
#include "compiler.h"
#include "debug_vm.h"
#include "parser.h"
#include "scanner.h"
#include "visual_decaf.h"
#include <iostream>
#include <streambuf>

using namespace decaf;
int main() {
    int id = get_id();
    std::string code = "int x;";
    upload_code(code.c_str(), id);
    std::string tokens = get_token_stream(id);
    std::cout << tokens << std::endl;
}