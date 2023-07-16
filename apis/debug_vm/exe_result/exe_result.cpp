#include "exe_result.h"

boost::json::value decaf::ExeResult::to_json() {
    boost::json::array list;
    for (Step step: steps) {
        list.emplace_back(step.to_json());
    }
    boost::json::object result{
        {"steps", list}};
    if (this->table == nullptr) {
        result["table"] = nullptr;
    } else {
        result["table"] = this->table->to_json();
    }
    return result;
}
