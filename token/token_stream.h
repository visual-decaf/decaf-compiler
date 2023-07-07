#pragma once

#include "serializable.h"
#include "token.h"
#include <vector>

namespace decaf {

class token_stream: public std::vector<token>, serializable {
public:
    // use vector's constructors
    using std::vector<token>::vector;

    boost::json::value to_json() override;
};

} // namespace decaf