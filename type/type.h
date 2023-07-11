#pragma once
#include <map>
#include <string>
namespace decaf {

struct Type {
    enum class Classification {
        INVALID,
        INT,
        DOUBLE,
        BOOL
    };

    static const std::map<Classification, std::string> type_name_of;

    Classification classification = Classification::INVALID;
    // TODO: Add function union type here
};

} // namespace decaf