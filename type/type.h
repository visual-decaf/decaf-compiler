#pragma once
#include "serializable.h"
#include <map>
#include <string>
namespace decaf {

struct Type: public Serializable {
    enum class Classification {
        INVALID,
        INT,
        DOUBLE,
        BOOL
    };

    static const std::map<Classification, std::string> type_name_of;

    Type() = default;

    explicit Type(const Classification& classification) {
        this->classification = classification;
    }

    Classification classification = Classification::INVALID;
    // TODO: Add function union type here

    boost::json::value to_json() override;
};

} // namespace decaf