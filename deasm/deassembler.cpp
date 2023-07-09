#include "deassembler.h"

using namespace decaf;

void Deassembler::op_PLUS() {
    this->assembly_code.emplace_back("PLUS");
}

void Deassembler::op_MINUS() {
    this->assembly_code.emplace_back("MINUS");
}

void Deassembler::op_MULTIPLY() {
    this->assembly_code.emplace_back("MULTIPLY");
}

void Deassembler::op_DIVIDE() {
    this->assembly_code.emplace_back("DIVIDE");
}

void Deassembler::op_MOD() {
    this->assembly_code.emplace_back("MOD");
}

void Deassembler::op_GET_INSTANT(uint8_t instant) {
    this->assembly_code.emplace_back("GET_INSTANT " + instant);
}

Deassembler::assembly_code_type Deassembler::get_code() {
    return this->assembly_code;
}
