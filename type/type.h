#pragma once

namespace decaf {

struct Type {
    enum class Classification {
        INVALID,
        INT,
        DOUBLE,
        BOOL
    };

    Classification classification = Classification::INVALID;
    // TODO: Add function union type here
};

} // namespace decaf