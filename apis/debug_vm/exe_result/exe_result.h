#pragma once

#include <utility>

#include "serializable.h"
#include "step.h"
#include "symbol_table.h"

namespace decaf {

class ExeResult: Serializable {
public:
    ExeResult(std::vector<decaf::Step> _steps, std::shared_ptr<decaf::SymbolTable> _table):
        steps(std::move(_steps)), table(std::move(_table)) {
    }

    boost::json::value to_json() override;

private:
    std::vector<decaf::Step> steps;
    std::shared_ptr<decaf::SymbolTable> table;
};

} // namespace decaf