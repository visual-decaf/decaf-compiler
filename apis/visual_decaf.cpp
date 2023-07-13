#include "visual_decaf.h"
#include "compiler.h"
#include "parser.h"
#include "vm.h"
#include <cstring>
#include <map>
#include <random>
#include <sstream>
#include <string>

std::map<int, decaf::TokenStream> token_streams;
std::map<int, std::shared_ptr<decaf::ast::Expr>> asts;
std::map<int, decaf::Program> programs;
std::map<int, decaf::VirtualMachine> vms;

std::uniform_int_distribution<int> dist(1, 2147483647);

int get_id() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    int id = dist(gen);
    return id;
}

void compile(const char* code, int id) {
    std::istringstream input{std::string(code)};
    decaf::Scanner scanner{input};
    scanner.scan();
    auto token_stream = scanner.get_tokens();
    decaf::Parser parser{token_stream};
    parser.parse();
    auto ast = parser.get_ast();
    decaf::Compiler compiler{ast};
    compiler.compile();
    auto program = compiler.get_program();
    token_streams.insert_or_assign(id, token_stream);
    asts.insert_or_assign(id, ast);
    programs.insert_or_assign(id, program);
    vms.insert_or_assign(id, decaf::VirtualMachine{program});
}

char* get_token_stream(int id) {
    auto json = boost::json::serialize(token_streams.at(id).to_json());
    char* token_stream = (char*) malloc((json.length() + 1) * sizeof(char));
    strcpy(token_stream, json.c_str());
    return token_stream;
}

char* get_ast(int id) {
    auto json = boost::json::serialize(asts.at(id)->to_json());
    char* ast = (char*) malloc((json.length() + 1) * sizeof(char));
    strcpy(ast, json.c_str());
    return ast;
}

char* get_program(int id) {
    auto json = boost::json::serialize(programs.at(id).to_json());
    char* program = (char*) malloc((json.length() + 1) * sizeof(char));
    strcpy(program, json.c_str());
    return program;
}