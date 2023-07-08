#include "byte_code.h"
#include <iomanip>

void decaf::ByteCode::emit(decaf::ByteCode::code_type b) {
    code_stream.push_back(b);
}

std::ostream& operator<<(std::ostream& os, const decaf::ByteCode& code) {
    for (auto& current_byte: code.code_stream) {
        os << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(current_byte);
    }
    return os;
}
