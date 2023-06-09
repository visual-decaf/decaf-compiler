#pragma once

#include "parser_impl.h"
#include "serializable.h"
#include <iostream>
#include <map>
#include <string>

namespace decaf {

using token_type = yy::parser::token_kind_type;
extern std::map<token_type, std::string> token_name_of;

class Token: public Serializable {
public:
    token_type type;
    std::string lexeme;

    Token(token_type _type, const std::string& lexeme = "");

    bool operator==(const Token& rhs) const;

    boost::json::value to_json() override;
};

} // namespace decaf

std::ostream& operator<<(std::ostream& os, const decaf::Token& tok);