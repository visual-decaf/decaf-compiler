#include "token_stream.h"

boost::json::value decaf::TokenStream::to_json() {
    boost::json::array result;
    for (auto& tok: *this) {
        result.emplace_back(tok.to_json());
    }
    return result;
}
