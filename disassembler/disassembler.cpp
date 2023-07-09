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
    this->assembly_code.emplace_back("GET_INSTANT " + instant);
}

Disassembler::assembly_code_type Disassembler::get_code() {
    return this->assembly_code;
}
