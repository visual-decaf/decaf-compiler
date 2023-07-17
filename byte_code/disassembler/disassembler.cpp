#include "disassembler.h"

using namespace decaf;

void Disassembler::run() {
    ByteCodeDriver driver{byte_code, *this};
    driver.produce();
}

bool Disassembler::op_PLUS() {
    this->assembly_code.emplace_back("PLUS");
    one_byte();
    return true;
}

bool Disassembler::op_MINUS() {
    this->assembly_code.emplace_back("MINUS");
    one_byte();
    return true;
}

bool Disassembler::op_MULTIPLY() {
    this->assembly_code.emplace_back("MULTIPLY");
    one_byte();
    return true;
}

bool Disassembler::op_DIVIDE() {
    this->assembly_code.emplace_back("DIVIDE");
    one_byte();
    return true;
}

bool Disassembler::op_MOD() {
    this->assembly_code.emplace_back("MOD");
    one_byte();
    return true;
}

bool Disassembler::op_GET_INSTANT(uint8_t instant) {
    this->assembly_code.emplace_back("GET_INSTANT " + std::to_string(static_cast<int>(instant)));
    two_byte();
    return true;
}

bool decaf::Disassembler::op_GET_INT_CONSTANT(uint8_t index) {
    this->assembly_code.emplace_back("GET_INT_CONSTANT " + std::to_string(static_cast<int>(index)));
    two_byte();
    return true;
}

bool Disassembler::op_GET_TRUE() {
    this->assembly_code.emplace_back("GET_TRUE");
    one_byte();
    return true;
}

bool Disassembler::op_GET_FALSE() {
    this->assembly_code.emplace_back("GET_FALSE");
    one_byte();
    return true;
}


bool Disassembler::op_LOGIC_AND() {
    this->assembly_code.emplace_back("LOGIC_AND");
    one_byte();
    return true;
}

bool Disassembler::op_LOGIC_OR() {
    this->assembly_code.emplace_back("LOGIC_OR");
    one_byte();
    return true;
}

bool Disassembler::op_NEGATE() {
    this->assembly_code.emplace_back("NEGATE");
    one_byte();
    return true;
}

bool Disassembler::op_LOGIC_NOT() {
    this->assembly_code.emplace_back("LOGIC_NOT");
    one_byte();
    return true;
}

bool Disassembler::op_LESS() {
    this->assembly_code.emplace_back("LESS");
    one_byte();
    return true;
}

bool Disassembler::op_LESS_EQUAL() {
    this->assembly_code.emplace_back("LESS_EQUAL");
    one_byte();
    return true;
}

bool Disassembler::op_GREATER() {
    this->assembly_code.emplace_back("GREATER");
    one_byte();
    return true;
}

bool Disassembler::op_GREATER_EQUAL() {
    this->assembly_code.emplace_back("GREATER_EQUAL");
    one_byte();
    return true;
}

bool Disassembler::op_EQUAL() {
    this->assembly_code.emplace_back("EQUAL");
    one_byte();
    return true;
}
bool Disassembler::op_NOT_EQUAL() {
    this->assembly_code.emplace_back("NOT_EQUAL");
    one_byte();
    return true;
}

bool Disassembler::op_GET_FLOAT_CONSTANT(uint8_t index) {
    this->assembly_code.emplace_back("GET_FLOAT_CONSTANT " + std::to_string(static_cast<int>(index)));
    two_byte();
    return true;
}

bool Disassembler::op_DISCARD() {
    this->assembly_code.emplace_back("DISCARD");
    one_byte();
    return true;
}

bool Disassembler::op_PRINT(uint8_t count) {
    this->assembly_code.emplace_back("PRINT " + std::to_string(static_cast<int>(count)));
    two_byte();
    return true;
}

bool Disassembler::op_SYMBOL_ADD(uint8_t index) {
    this->assembly_code.emplace_back("SYMBOL_ADD " + std::to_string(static_cast<int>(index)));
    two_byte();
    return true;
}

bool Disassembler::op_SYMBOL_GET(uint8_t index) {
    this->assembly_code.emplace_back("SYMBOL_GET " + std::to_string(static_cast<int>(index)));
    two_byte();
    return true;
}

bool Disassembler::op_SYMBOL_SET() {
    this->assembly_code.emplace_back("SYMBOL_SET");
    one_byte();
    return true;
}

bool Disassembler::op_GET_FLOAT_ZERO() {
    this->assembly_code.emplace_back("GET_FLOAT_ZERO");
    one_byte();
    return true;
}

bool Disassembler::op_GOTO(ByteCodeDriver&, uint8_t index) {
    this->assembly_code.emplace_back("GOTO " + std::to_string(static_cast<int>(index)));
    two_byte();
    return true;
}

bool Disassembler::op_GOTO_IF_FALSE(ByteCodeDriver&, uint8_t index) {
    this->assembly_code.emplace_back("GOTO_IF_FALSE " + std::to_string(static_cast<int>(index)));
    two_byte();
    return true;
}

bool Disassembler::op_GET_STRING_CONSTANT(uint8_t index) {
    this->assembly_code.emplace_back("GET_STRING_CONSTANT " + std::to_string(static_cast<int>(index)));
    two_byte();
    return true;
}

int Disassembler::get_line(uint8_t index) {
    return byte_to_line.at(index);
}

void Disassembler::one_byte() {
    byte_to_line.insert_or_assign(curr_byte, curr_line);
    curr_byte++;
    curr_line++;
}

void Disassembler::two_byte() {
    byte_to_line.insert_or_assign(curr_line, curr_line);
    curr_byte += 2;
    curr_line++;
}

Disassembler::assembly_code_type Disassembler::get_code() {
    return this->assembly_code;
}