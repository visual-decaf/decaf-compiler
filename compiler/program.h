#pragma once

#include "byte_code.h"

namespace decaf {

// TODO: Add constant table later here
class Program {
public:
    void emit(ByteCode::code_type b) {
        code.emit(b);
    }

    void emit_bytes(ByteCode::code_type b1,
                    ByteCode::code_type b2) {
        code.emit(b1);
        code.emit(b2);
    }

private:
    ByteCode code;
};

} // namespace decaf