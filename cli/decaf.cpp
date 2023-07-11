#include "compiler.h"
#include "parser.h"
#include "scanner.h"
#include "version.h"
#include "vm.h"

#include <iostream>

void run_repl() {
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

        decaf::Compiler compiler{ast_root};
        compiler.compile();
        auto program = compiler.get_program();

        decaf::VirtualMachine vm{program};
        vm.run();
        auto result = vm.get_result();
        std::cout << std::get<int>(result) << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Visual Decaf " PROJECT_VERSION << std::endl;
    run_repl();
    return 0;
}