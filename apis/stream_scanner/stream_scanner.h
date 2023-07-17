#pragma once

#include "scanner.h"
#include "sstream"

namespace decaf {

class StreamScanner {
public:
    std::istringstream is;
    Scanner scanner;

    explicit StreamScanner(const std::string& input):
        is{input}, scanner{is} {
    }

    TokenStream get_tokens();
    void scan();
    void scan_line();

    bool is_error() const;
    void clear_error();
};

} // namespace decaf