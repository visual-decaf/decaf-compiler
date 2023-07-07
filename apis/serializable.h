#include <boost/json.hpp>

namespace decaf {

class serializable {
    virtual boost::json::value to_json() = 0;
};

} // namespace decaf
