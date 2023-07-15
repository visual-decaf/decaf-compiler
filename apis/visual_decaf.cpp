#include "visual_decaf.h"
#include "compiler.h"
#include "parser.h"
#include "stream_scanner.h"
#include "vm.h"
#include <cstring>
#include <map>
#include <random>
#include <string>

std::map<int, decaf::StreamScanner*> stream_scanners;
std::map<int, decaf::Parser*> parsers;
std::map<int, decaf::Compiler*> compilers;
std::map<int, decaf::VirtualMachine*> vms;

std::uniform_int_distribution<int> dist(1, 2147483647);

static void write_error_msg(const char* error_code, boost::json::array& error_msg, char*& response);
static void write_success_result(boost::json::value& result, char*& response);

int get_id() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    int id = dist(gen);
    stream_scanners.insert_or_assign(id, nullptr);
    parsers.insert_or_assign(id, nullptr);
    compilers.insert_or_assign(id, nullptr);
    vms.insert_or_assign(id, nullptr);
    return id;
}

char* upload_code(const char* code, int id) {
    char* response = nullptr;
    if (stream_scanners.find(id) == stream_scanners.end()) {
        boost::json::array error_msg;
        error_msg.emplace_back("Invalid ID");
        write_error_msg("6", error_msg, response);
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
        boost::json::array error_msg;
        error_msg.emplace_back("Invalid ID");
        write_error_msg("6", error_msg, response);
        return response;
    }
    auto stream_scanner = stream_scanners.at(id);
    stream_scanner->scan();
    if (stream_scanner->is_error()) {
        boost::json::array error_msg;
        error_msg.emplace_back("Unrecognized token");
        write_error_msg("2", error_msg, response);
        return response;
    }
    boost::json::object response_object{
        {"code", "1"},
        {"msg", "success"},
        {"result", stream_scanner->get_tokens().to_json()}};
    std::string response_json = boost::json::serialize(response_object);
    response = (char*) malloc((response_json.length() + 1) * sizeof(char));
    strcpy(response, response_json.c_str());
    return response;
}

char* get_ast(int id) {
    char* response = nullptr;
    if (parsers.find(id) == parsers.end()) {
        boost::json::array error_msg;
        error_msg.emplace_back("Invalid ID");
        write_error_msg("6", error_msg, response);
        return response;
    }
    if (stream_scanners.at(id)->is_error()) {
        boost::json::array error_msg;
        error_msg.emplace_back("There are some wrongs at scan phase");
        write_error_msg("3", error_msg, response);
        return response;
    }
    if (parsers.at(id) != nullptr) {
        delete parsers.at(id);
    }
    auto parser = new decaf::Parser{stream_scanners.at(id)->get_tokens()};
    parsers.insert_or_assign(id, parser);
    parser->parse();
    if (parser->is_error()) {
        boost::json::array err_msg_arr;
        auto err_msgs = parser->get_err_messages();
        for (const auto& err_msg: err_msgs) {
            err_msg_arr.emplace_back(err_msg);
        }
        write_error_msg("4", err_msg_arr, response);
        return response;
    }
    boost::json::array list;
    const decaf::Parser::stmt_list& stmt_list = parser->get_stmt_list();
    for (const auto& stmt: stmt_list) {
        list.emplace_back(stmt->to_json());
    }
    boost::json::value result{
        {"type", "StmtsList"},
        {"name", "StmtsList"},
        {"list", list},
        {"resultType", "VOID"}};
    write_success_result(result, response);
    return response;
}

char* get_program(int id) {
    char* response = nullptr;
    if (compilers.find(id) == compilers.end()) {
        boost::json::array error_msg;
        error_msg.emplace_back("Invalid ID");
        write_error_msg("6", error_msg, response);
        return response;
    }
    if (stream_scanners.at(id)->is_error() || parsers.at(id)->is_error()) {
        boost::json::array error_msg;
        error_msg.emplace_back("There are some wrongs at parse phase");
        write_error_msg("5", error_msg, response);
        return response;
    }
    if (compilers.at(id) != nullptr) {
        delete compilers.at(id);
    }
    auto compiler = new decaf::Compiler{parsers.at(id)->get_stmt_list()};
    compilers.insert_or_assign(id, compiler);
    compiler->compile();
    boost::json::value result = compiler->get_program().to_json();
    write_success_result(result, response);
    return response;
}

void write_error_msg(const char* error_code, boost::json::array& error_msg, char*& response) {
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