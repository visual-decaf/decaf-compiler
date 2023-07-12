#include "disassembler.h"

using namespace decaf;

void Disassembler::op_PLUS() {
    this->assembly_code.emplace_back("PLUS");
}

void Disassembler::op_MINUS() {
    this->assembly_code.emplace_back("MINUS");
}

void Disassembler::op_MULTIPLY() {
    this->assembly_code.emplace_back("MULTIPLY");
}

void Disassembler::op_DIVIDE() {
    this->assembly_code.emplace_back("DIVIDE");
}

void Disassembler::op_MOD() {
    this->assembly_code.emplace_back("MOD");
}

void Disassembler::op_GET_INSTANT(uint8_t instant) {
    this->assembly_code.emplace_back("GET_INSTANT " + std::to_string(static_cast<int>(instant)));
}

void decaf::Disassembler::op_GET_INT_CONSTANT(uint8_t index) {
    this->assembly_code.emplace_back("GET_INT_CONSTANT " + std::to_string(static_cast<int>(index)));
}

void Disassembler::op_GET_TRUE() {
    this->assembly_code.emplace_back("GET_TRUE");
}

void Disassembler::op_GET_FALSE() {
    this->assembly_code.emplace_back("GET_FALSE");
}

Disassembler::assembly_code_type Disassembler::get_code() {
    return this->assembly_code;
}

void Disassembler::op_LOGIC_AND() {
    this->assembly_code.emplace_back("LOGIC_AND");
}

void Disassembler::op_LOGIC_OR() {
    this->assembly_code.emplace_back("LOGIC_OR");
}

void Disassembler::op_NEGATE() {
    this->assembly_code.emplace_back("NEGATE");
}

void Disassembler::op_LOGIC_NOT() {
    this->assembly_code.emplace_back("LOGIC_NOT");
}

void Disassembler::op_LESS() {
    this->assembly_code.emplace_back("LESS");
}

void Disassembler::op_LESS_EQUAL() {
    this->assembly_code.emplace_back("LESS_EQUAL");
}

void Disassembler::op_GREATER() {
    this->assembly_code.emplace_back("GREATER");
}

void Disassembler::op_GREATER_EQUAL() {
    this->assembly_code.emplace_back("GREATER_EQUAL");
}
