#pragma once

#include <utility>

#include "serializable.h"
#include "step.h"
#include "symbol_table.h"

namespace decaf {

class ExeResult: Serializable {
public:
    ExeResult(int _line, std::vector<decaf::Step> _steps, boost::json::value _table):
        line(_line), steps(std::move(_steps)), table(std::move(_table)) {
    }

    boost::json::value to_json() override;

private:
    int line;
    std::vector<decaf::Step> steps;
    boost::json::value table;
};

} // namespace decaf