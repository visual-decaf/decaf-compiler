#pragma once
#include <map>
#include <string>
#include "serializable.h"
namespace decaf {

struct Type : public serializable {
    enum class Classification {
        INVALID,
        INT,
        DOUBLE,
        BOOL
    };

    static const std::map<Classification, std::string> type_name_of;

    Classification classification = Classification::INVALID;
    // TODO: Add function union type here

    boost::json::value to_json() override;
};

} // namespace decaf