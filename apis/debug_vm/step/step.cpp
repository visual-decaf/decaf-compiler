#include "step.h"

#include <utility>

void decaf::Step::set_error_msg(std::string _error_msg) {
    this->error_msg = std::move(_error_msg);
}

boost::json::value decaf::Step::to_json() {
    boost::json::object result{{"operation", operation}};
    if (operation == "POP") {
        result["item"] = nullptr;
    } else if (operation == "ERROR") {
        result["item"] = error_msg;
    } else {
        if (this->item == nullptr) {
            result["item"] = nullptr;
        } else {
            result["item"] = this->item->to_json();
        }
    }
    return result;
}
