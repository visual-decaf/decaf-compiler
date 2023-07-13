#pragma once

#include <boost/json.hpp>

namespace decaf {

class Serializable {
public:
    virtual boost::json::value to_json() = 0;
    virtual ~Serializable() = default;
};

} // namespace decaf
