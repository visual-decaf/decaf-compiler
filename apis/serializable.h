#pragma once

#include <boost/json.hpp>

namespace decaf {

class serializable {
public:
    virtual boost::json::value to_json() = 0;
    virtual ~serializable() = default;
};

} // namespace decaf
