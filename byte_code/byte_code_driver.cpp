#include "byte_code_driver.h"

void decaf::ByteCodeDriver::produce() {
    while (current_byte != code_stream.end()) {
        produce_instruction();
        current_byte++;
    }
}

// Contract
// PreCondition: current_byte is set to the beginning of next instruction
// PostCondition: current_byte is set to the end of produced instruction
void decaf::ByteCodeDriver::produce_instruction() {
    using Instruction = ByteCode::Instruction;
    switch (*current_byte) {
        // No Operands
        case Instruction ::PLUS:
            visitor.op_PLUS();
            break;
        case Instruction ::MINUS:
            visitor.op_MINUS();
            break;
        case Instruction ::MULTIPLY:
            visitor.op_MULTIPLY();
            break;
        case Instruction ::DIVIDE:
            visitor.op_DIVIDE();
            break;

            // 0 Operand
        case Instruction ::GET_INSTANT:
            check_expected_byte(1);
            visitor.op_GET_INSTANT(*(current_byte++));
            break;
    }
}
bool decaf::ByteCodeDriver::check_expected_byte(int count) {
    return count <= std::distance(current_byte, code_stream.end());
}
