#include "visual_decaf.h"
#include "compiler.h"
#include "parser.h"
#include <map>
#include <random>
#include <sstream>
#include <string>

std::map<int, const char*> token_streams;
std::map<int, const char*> asts;
std::map<int, const char*> programs;

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
    token_streams.insert(std::make_pair(id, boost::json::serialize(token_stream.to_json()).c_str()));
    asts.insert(std::make_pair(id, boost::json::serialize(ast->to_json()).c_str()));
    programs.insert(std::make_pair(id, boost::json::serialize(program.to_json()).c_str()));
}

const char* get_token_stream(int id) {
    return token_streams.at(id);
}

const char* get_ast(int id) {
    return asts.at(id);
}

const char* get_program(int id) {
    return programs.at(id);
}