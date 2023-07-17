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
    std::string input = R"(int x = 1 + 2 * 3;

if (x == 7)
    Print("Yes");
else
    Print("No");)";
    std::istringstream input_code{input};
    Scanner scanner{input_code};
    scanner.scan();
    Parser parser{scanner.get_tokens()};
    parser.parse();
    Compiler compiler{parser.get_stmt_list()};
    compiler.compile();
    DebugVirtualMachine debug_vm{compiler.get_program()};
    debug_vm.run();
}