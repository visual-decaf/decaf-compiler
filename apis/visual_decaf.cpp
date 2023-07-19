#include "visual_decaf.h"
#include "compiler.h"
#include "debug_vm.h"
#include "parser.h"
#include "stream_scanner.h"
#include <cstring>
#include <map>
#include <random>
#include <string>

std::map<int, decaf::StreamScanner*> stream_scanners;
std::map<int, decaf::Parser*> parsers;
std::map<int, decaf::Compiler*> compilers;
std::map<int, decaf::DebugVirtualMachine*> debug_vms;

std::uniform_int_distribution<int> dist(1, 2147483647);

static void write_error_msg(std::string error_code, std::string error_msg, char*& response);
static void write_success_result(boost::json::value& result, char*& response);

int get_id() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    int id = dist(gen);
    stream_scanners.insert_or_assign(id, nullptr);
    parsers.insert_or_assign(id, nullptr);
    compilers.insert_or_assign(id, nullptr);
    debug_vms.insert_or_assign(id, nullptr);
    return id;
}

char* upload_code(const char* code, int id) {
    char* response = nullptr;
    if (stream_scanners.find(id) == stream_scanners.end()) {
        write_error_msg("6", "Invalid ID", response);
        return response;
    }
    if (stream_scanners.at(id) != nullptr) {
        delete stream_scanners.at(id);
    }
    stream_scanners.insert_or_assign(id, new decaf::StreamScanner{code});
    boost::json::object response_object{
        {"code", "1"},
        {"msg", "Success"}};
    auto response_json = boost::json::serialize(response_object);
    response = (char*) malloc((response_json.length() + 1) * sizeof(char));
    strcpy(response, response_json.c_str());
    return response;
}

char* get_token_stream(int id) {
    char* response = nullptr;
    if (stream_scanners.find(id) == stream_scanners.end()) {
        write_error_msg("6", "Invalid ID", response);
        return response;
    }
    auto stream_scanner = stream_scanners.at(id);
    if (stream_scanner == nullptr) {
        write_error_msg("7", "Please Unload Code First Before Scanning", response);
        return response;
    }
    stream_scanner->scan();
    if (stream_scanner->is_error()) {
        write_error_msg("2", "Unrecognized token", response);
        return response;
    }
    auto tokens = stream_scanner->get_tokens().to_json();
    write_success_result(tokens, response);
    return response;
}

char* get_ast(int id) {
    char* response = nullptr;
    if (parsers.find(id) == parsers.end()) {
        write_error_msg("6", "Invalid ID", response);
        return response;
    }
    if (stream_scanners.at(id) == nullptr) {
        write_error_msg("7", "Please Get Tokens First Before Parsing", response);
    }
    if (stream_scanners.at(id)->is_error()) {
        write_error_msg("3", "There are some wrongs at scan phase", response);
        return response;
    }
    if (parsers.at(id) != nullptr) {
        delete parsers.at(id);
    }
    auto parser = new decaf::Parser{stream_scanners.at(id)->get_tokens()};
    parsers.insert_or_assign(id, parser);
    parser->parse();
    if (parser->is_error()) {
        write_error_msg("4", parser->get_err_messages().front(), response);
        return response;
    }
    boost::json::array list;
    const decaf::Parser::stmt_list& stmt_list = parser->get_stmt_list();
    for (const auto& stmt: stmt_list) {
        list.emplace_back(boost::json::object{{"relation", ""},
                                              {"stmt", stmt->to_json()}});
    }
    boost::json::object stmts_object{
        {"type", "StmtsList"},
        {"name", "Program"},
        {"list", list},
        {"resultType", "VOID"}};
    boost::json::value result{
        {"relation", ""},
        {"stmt", stmts_object}};
    write_success_result(result, response);
    return response;
}

char* get_program(int id) {
    char* response = nullptr;
    if (compilers.find(id) == compilers.end()) {
        write_error_msg("6", "Invalid ID", response);
        return response;
    }
    if (parsers.at(id) == nullptr) {
        write_error_msg("7", "Please Get AST First Before Compiling", response);
        return response;
    }
    if (parsers.at(id)->is_error()) {
        write_error_msg("5", "There are some wrongs at parse phase", response);
        return response;
    }
    if (compilers.at(id) != nullptr) {
        delete compilers.at(id);
    }
    auto compiler = new decaf::Compiler{parsers.at(id)->get_stmt_list()};
    compilers.insert_or_assign(id, compiler);
    compiler->compile();
    // compiler will not occur errors
    boost::json::value result = compiler->get_program().to_json();
    write_success_result(result, response);
    return response;
}

char* get_debug_info(int id) {
    char* response = nullptr;
    if (debug_vms.find(id) == debug_vms.end()) {
        write_error_msg("6", "Invalid ID", response);
        return response;
    }
    if (compilers.at(id) == nullptr) {
        write_error_msg("7", "Please Get Program First Before Debug", response);
        return response;
    }
    if (debug_vms.at(id) != nullptr) {
        delete debug_vms.at(id);
    }
    auto debug_vm = new decaf::DebugVirtualMachine{compilers.at(id)->get_program()};
    debug_vms.insert_or_assign(id, debug_vm);
    debug_vm->run();
    // debug_vm will stop if an error occurs
    auto result = debug_vm->get_exe_results_json();
    write_success_result(result, response);
    return response;
}

void end_use(int id) {
    if (stream_scanners.find(id) != stream_scanners.end() && stream_scanners.at(id) != nullptr) {
        delete stream_scanners.at(id);
    }
    if (parsers.find(id) != parsers.end() && parsers.at(id) != nullptr) {
        delete parsers.at(id);
    }
    if (compilers.find(id) != compilers.end() && compilers.at(id) != nullptr) {
        delete compilers.at(id);
    }
    if (debug_vms.find(id) != debug_vms.end() && debug_vms.at(id) != nullptr) {
        delete debug_vms.at(id);
    }
}

void write_error_msg(std::string error_code, std::string error_msg, char*& response) {
    boost::json::object response_object{
        {"code", error_code},
        {"msg", error_msg}};
    auto response_json = boost::json::serialize(response_object);
    response = (char*) malloc((response_json.length() + 1) * sizeof(char));
    strcpy(response, response_json.c_str());
}

void write_success_result(boost::json::value& result, char*& response) {
    boost::json::object response_object{
        {"code", "1"},
        {"msg", "Success"},
        {"result", result}};
    auto response_json = boost::json::serialize(response_object);
    response = (char*) malloc((response_json.length() + 1) * sizeof(char));
    strcpy(response, response_json.c_str());
}