#include "byte_code_separate.h"
#include "byte_code_driver.h"

void decaf::ByteCodeSeparate::op_PLUS() {
    op_stream.push_back(Instruction ::PLUS);
}

void decaf::ByteCodeSeparate::op_MINUS() {
    op_stream.push_back(Instruction ::MINUS);
}

void decaf::ByteCodeSeparate::op_MULTIPLY() {
    op_stream.push_back(Instruction ::MULTIPLY);
}

void decaf::ByteCodeSeparate::op_DIVIDE() {
    op_stream.push_back(Instruction ::DIVIDE);
}

void decaf::ByteCodeSeparate::op_MOD() {
    op_stream.push_back(Instruction ::MOD);
}

void decaf::ByteCodeSeparate::op_GET_INSTANT(uint8_t instant) {
    op_stream.push_back(Instruction ::GET_INSTANT);
    op_stream.push_back(instant);
}

void decaf::ByteCodeSeparate::op_GET_INT_CONSTANT(uint8_t index) {
    op_stream.push_back(Instruction ::GET_INT_CONSTANT);
    intconstant_stream.push_back(index);
}


void decaf::ByteCodeSeparate::Separate(ByteCode code) {
    op_stream.clear();
    intconstant_id_stream.clear();
    ByteCodeDriver driver{code, *this};
    driver.produce();
}
