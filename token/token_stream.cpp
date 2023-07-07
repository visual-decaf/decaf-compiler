#include "token_stream.h"

boost::json::value decaf::token_stream::to_json() {
    boost::json::array result;
    for (auto& tok: *this) {
        result.emplace_back(tok.to_json());
    }
    return result;
}
