#pragma once
#include "serializable.h"
#include <map>
#include <string>
namespace decaf {

struct Type: public Serializable {
    enum class Classification : uint8_t {
        INVALID,
        INT,
        FLOAT,
        BOOL,
        STRING,
        VOID
    };

    static const std::map<Classification, std::string> type_name_of;

    Type() = default;

    explicit Type(const Classification& classification) {
        this->classification = classification;
    }

    Classification classification = Classification::INVALID;
    // TODO: Add function union type here

    bool operator==(const Type& rhs) const {
        return classification == rhs.classification;
    }

    bool operator!=(const Type& rhs) const {
        return !(*this == rhs);
    }

    boost::json::value to_json() override;
    std::string name() const;
};

} // namespace decaf