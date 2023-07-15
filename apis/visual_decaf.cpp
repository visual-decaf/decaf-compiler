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

int get_id() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    int id = dist(gen);
    return id;
}

char* upload_code(const char* code, int id) {
    char* response = nullptr;
    if (stream_scanners.find(id) != stream_scanners.end() && stream_scanners.at(id) != nullptr) {
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
    auto stream_scanner = stream_scanners.at(id);
    char* response = nullptr;
    stream_scanner->scan();
    if (stream_scanner->is_error()) {
        boost::json::object response_object{
            {"code", "2"},
            {"msg", "Unrecognized token"}};
        std::string response_json = boost::json::serialize(response_object);
        response = (char*) malloc((response_json.length() + 1) * sizeof(char));
        strcpy(response, response_json.c_str());
    } else {
        boost::json::object response_object{
            {"code", "1"},
            {"msg", "success"},
            {"result", stream_scanner->get_tokens().to_json()}};
        std::string response_json = boost::json::serialize(response_object);
        response = (char*) malloc((response_json.length() + 1) * sizeof(char));
        strcpy(response, response_json.c_str());
    }
    return response;
}

char* get_ast(int id) {
    if (parsers.find(id) != parsers.end() && parsers.at(id) != nullptr) {
        delete parsers.at(id);
    }
    char* response = nullptr;
    if (stream_scanners.at(id)->is_error()) {
        boost::json::object response_object{
            {"code", "3"},
            {"msg", "There are some wrongs at scan phase"}};
        std::string response_json = boost::json::serialize(response_object);
        response = (char*) malloc((response_json.length() + 1) * sizeof(char));
        strcpy(response, response_json.c_str());
        return response;
    }
    auto parser = new decaf::Parser{stream_scanners.at(id)->get_tokens()};
    parsers.insert_or_assign(id, parser);
    parser->parse();
    if (parser->is_error()) {
        boost::json::array err_msg_arr{};
        auto err_msgs = parser->get_err_messages();
        for (const auto& err_msg: err_msgs) {
            err_msg_arr.emplace_back(err_msg);
        }
        boost::json::object response_object{
            {"code", "4"},
            {"msg", err_msg_arr}};
        std::string response_json = boost::json::serialize(response_object);
        response = (char*) malloc((response_json.length() + 1) * sizeof(char));
        strcpy(response, response_json.c_str());
        return response;
    }
    boost::json::object response_object{
        {"code", "1"},
        {"msg", "Success"},
        {"result", parser->get_ast()->to_json()}};
    std::string response_json = boost::json::serialize(response_object);
    response = (char*) malloc((response_json.length() + 1) * sizeof(char));
    strcpy(response, response_json.c_str());
    return response;
}

char* get_program(int id) {
    if (compilers.find(id) != compilers.end() && compilers.at(id) != nullptr) {
        delete compilers.at(id);
    }
    char* response = nullptr;
    if (stream_scanners.at(id)->is_error() || parsers.at(id)->is_error()) {
        boost::json::object response_object{
            {"code", "5"},
            {"msg", "There are some wrongs at parse phase"}};
        std::string response_json = boost::json::serialize(response_object);
        response = (char*) malloc((response_json.length() + 1) * sizeof(char));
        strcpy(response, response_json.c_str());
        return response;
    }
    auto compiler = new decaf::Compiler{parsers.at(id)->get_ast()};
    compilers.insert_or_assign(id, compiler);
    compiler->compile();
    boost::json::object response_object{
        {"code", "1"},
        {"msg", "Success"},
        {"result", compiler->get_program().to_json()}};
    std::string response_json = boost::json::serialize(response_object);
    response = (char*) malloc((response_json.length() + 1) * sizeof(char));
    strcpy(response, response_json.c_str());
    return response;
}