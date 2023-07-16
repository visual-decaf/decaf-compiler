#pragma once

#include <utility>

#include "stack_items.h"

namespace decaf {

class Step: Serializable {
public:
    explicit Step(std::string _operation, boost::json::value _item_object = nullptr):
        operation(std::move(_operation)), item_object(std::move(_item_object)) {
    }

    void set_error_msg(std::string error_msg);

    boost::json::value to_json() override;

private:
    std::string operation;
    boost::json::value item_object;
    std::string error_msg;
};

} // namespace decaf