#pragma once

#include "parser_impl.h"
#include <map>
#include <string>

namespace decaf {

using token_type = yy::parser::token_kind_type;

class token {
public:
    token_type type;
    std::string lexeme;

    bool operator==(const token& rhs) const {
        return this->type == rhs.type && this->lexeme == rhs.lexeme;
    }
};


extern std::map<token_type, std::string> token_name_of;

} // namespace decaf