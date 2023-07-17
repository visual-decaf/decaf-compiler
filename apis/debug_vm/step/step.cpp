#include "step.h"

#include <utility>

void decaf::Step::set_error_msg(std::string _error_msg) {
    this->error_msg = std::move(_error_msg);
}

void decaf::Step::set_output(std::string _output) {
    this->output = std::move(_output);
}

boost::json::value decaf::Step::to_json() {
    boost::json::object result{{"operation", operation}};
    if (operation == "POP") {
        result["item"] = nullptr;
    } else if (operation == "ERROR") {
        result["item"] = error_msg;
    } else if (operation == "PRINT") {
        result["item"] = output;
    } else {
        result["item"] = item_object;
    }
    return result;
}