#include "visual_decaf.h"
#include "compiler.h"
#include "parser.h"
#include "stream_scanner.h"
#include "vm.h"
#include <cstring>
#include <map>
#include <random>
#include <sstream>
#include <string>

std::map<int, bool> scan_results;
std::map<int, decaf::TokenStream> token_streams;
std::map<int, decaf::Parser> parsers;
std::map<int, decaf::Compiler> compilers;
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
    scan_results.insert_or_assign(id, scanner.is_error());
    token_streams.insert_or_assign(id, scanner.get_tokens());
}

char* get_token_stream(int id) {
    char* token_stream = nullptr;
    if (scan_results.at(id)) {
        std::string error_msg = "Unrecognized token";
        token_stream = (char*) malloc((error_msg.length() + 1) * sizeof(char));
        strcpy(token_stream, error_msg.c_str());
    } else {
        std::string token_json = boost::json::serialize(token_streams.at(id).to_json());
        token_stream = (char*) malloc((token_json.length() + 1) * sizeof(char));
        strcpy(token_stream, token_json.c_str());
    }
    return token_stream;
}

char* get_ast(int id) {
}

char* get_program(int id) {
    auto json = boost::json::serialize(programs.at(id).to_json());
    char* program = (char*) malloc((json.length() + 1) * sizeof(char));
    strcpy(program, json.c_str());
    return program;
}