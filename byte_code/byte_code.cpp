#include "byte_code.h"
#include "byte_code_driver.h"
#include "disassembler.h"
#include <iomanip>

void decaf::ByteCode::emit(decaf::ByteCode::code_type b) {
    code_stream.push_back(b);
}

boost::json::value decaf::ByteCode::to_json() {
    decaf::Disassembler disassembler;
    decaf::ByteCodeDriver byte_code_driver{
        *this, disassembler};
    byte_code_driver.produce();
    std::vector<std::string> assembly_code = disassembler.get_code();
    boost::json::array result;
    for (auto& code: assembly_code) {
        result.emplace_back(code);
    }
    return result;
}


std::ostream& operator<<(std::ostream& os, const decaf::ByteCode& code) {
    for (auto& current_byte: code.code_stream) {
        os << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(current_byte);
    }
    return os;
}
