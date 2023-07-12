#pragma once

#include "serializable.h"
#include "token.h"
#include <vector>

namespace decaf {

class TokenStream: public std::vector<Token>, Serializable {
public:
    // use vector's constructors
    using std::vector<Token>::vector;

    boost::json::value to_json() override;
};

} // namespace decaf