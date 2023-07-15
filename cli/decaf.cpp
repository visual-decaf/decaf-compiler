#include "compiler.h"
#include "parser.h"
#include "scanner.h"
#include "version.h"
#include "vm.h"

#include <iostream>

void print_result(decaf::StackItem::ptr_type result) {
    if (result == nullptr) {
        return;
    }
    std::cout << *result << std::endl;
}

void run_repl() {
    decaf::Compiler compiler;
    while (true) {
        std::cout << ">> ";
        decaf::Scanner scanner{std::cin};
        scanner.scan_line();
        auto token_stream = scanner.get_tokens();
        token_stream.emplace_back(decaf::token_type::YYEOF);

        decaf::Parser parser{token_stream};
        parser.parse();
        auto ast_root = parser.get_ast();
        if (ast_root == nullptr) {
            return;
        }

        compiler.compile();
        auto program = compiler.get_program();

        decaf::VirtualMachine vm{program};
        vm.run();
        auto result = vm.get_stack_top();
        print_result(result);
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Visual Decaf " PROJECT_VERSION << std::endl;
    run_repl();
    return 0;
}