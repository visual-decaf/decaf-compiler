#pragma once

#include <utility>

#include "stack_items.h"

namespace decaf {

class Step: Serializable {
public:
    Step(std::string _operation, std::shared_ptr<decaf::StackItem> _item):
        operation(std::move(_operation)), item(std::move(_item)) {
    }

    void set_error_msg(std::string error_msg);

    boost::json::value to_json() override;

private:
    std::string operation;
    std::shared_ptr<decaf::StackItem> item;
    std::string error_msg;
};

} // namespace decaf