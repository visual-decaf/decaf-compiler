#include "stream_scanner.h"

decaf::TokenStream decaf::StreamScanner::get_tokens() {
    return this->scanner.get_tokens();
}

void decaf::StreamScanner::scan() {
    this->scanner.scan();
}

void decaf::StreamScanner::scan_line() {
    this->scanner.scan_line();
}

bool decaf::StreamScanner::is_error() const {
    return this->scanner.is_error();
}

void decaf::StreamScanner::clear_error() {
    this->scanner.clear_error();
}
