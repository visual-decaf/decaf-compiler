#include "compiler.h"
#include "parser.h"
#include "scanner.h"
#include "version.h"
#include "vm.h"

#include <fstream>
#include <iostream>

void print_result(decaf::StackItem::ptr_type result) {
    if (result == nullptr) {
        return;
    }
    std::cout << *result << std::endl;
}

void run_repl() {
    std::cout << "Visual Decaf " PROJECT_VERSION << std::endl;
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

void run_file(const char* file_name) {
    std::ifstream is{file_name};
    decaf::Scanner scanner{is};
    scanner.scan();
    auto token_stream = scanner.get_tokens();

    decaf::Parser parser{token_stream};
    parser.parse();
    auto stmts = parser.get_stmt_list();

    decaf::Compiler compiler{stmts};
    compiler.compile();
    auto program = compiler.get_program();

    decaf::VirtualMachine vm{program};
    vm.run();
    auto result = vm.get_stack_top();
    print_result(result);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: decaf_cli file";
        return 1;
    }

    run_file(argv[1]);
    return 0;
}