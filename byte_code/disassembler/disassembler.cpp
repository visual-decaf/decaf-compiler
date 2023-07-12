#include "disassembler.h"

using namespace decaf;

bool Disassembler::op_PLUS() {
    this->assembly_code.emplace_back("PLUS");
    return true;
}

bool Disassembler::op_MINUS() {
    this->assembly_code.emplace_back("MINUS");
    return true;
}

bool Disassembler::op_MULTIPLY() {
    this->assembly_code.emplace_back("MULTIPLY");
    return true;
}

bool Disassembler::op_DIVIDE() {
    this->assembly_code.emplace_back("DIVIDE");
    return true;
}

bool Disassembler::op_MOD() {
    this->assembly_code.emplace_back("MOD");
    return true;
}

bool Disassembler::op_GET_INSTANT(uint8_t instant) {
    this->assembly_code.emplace_back("GET_INSTANT " + std::to_string(static_cast<int>(instant)));
    return true;
}

bool decaf::Disassembler::op_GET_INT_CONSTANT(uint8_t index) {
    this->assembly_code.emplace_back("GET_INT_CONSTANT " + std::to_string(static_cast<int>(index)));
    return true;
}

bool Disassembler::op_GET_TRUE() {
    this->assembly_code.emplace_back("GET_TRUE");
    return true;
}

bool Disassembler::op_GET_FALSE() {
    this->assembly_code.emplace_back("GET_FALSE");
    return true;
}

Disassembler::assembly_code_type Disassembler::get_code() {
    return this->assembly_code;
}

bool Disassembler::op_LOGIC_AND() {
    this->assembly_code.emplace_back("LOGIC_AND");
    return true;
}

bool Disassembler::op_LOGIC_OR() {
    this->assembly_code.emplace_back("LOGIC_OR");
    return true;
}

bool Disassembler::op_NEGATE() {
    this->assembly_code.emplace_back("NEGATE");
    return true;
}

bool Disassembler::op_LOGIC_NOT() {
    this->assembly_code.emplace_back("LOGIC_NOT");
    return true;
}

bool Disassembler::op_LESS() {
    this->assembly_code.emplace_back("LESS");
    return true;
}

bool Disassembler::op_LESS_EQUAL() {
    this->assembly_code.emplace_back("LESS_EQUAL");
    return true;
}

bool Disassembler::op_GREATER() {
    this->assembly_code.emplace_back("GREATER");
    return true;
}

bool Disassembler::op_GREATER_EQUAL() {
    this->assembly_code.emplace_back("GREATER_EQUAL");
    return true;
}

bool Disassembler::op_EQUAL() {
    this->assembly_code.emplace_back("EQUAL");
    return true;
}
bool Disassembler::op_NOT_EQUAL() {
    this->assembly_code.emplace_back("NOT_EQUAL");
    return true;
}
