#include "byte_code.h"

void decaf::ByteCode::emit(decaf::ByteCode::code_type b) {
    code_stream.push_back(b);
}
