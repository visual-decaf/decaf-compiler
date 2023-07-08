#include "byte_code_visitor.h"

void decaf::ByteCodeVisitor::produce() {
    while (current_byte != code_stream.end()) {
        produce_instruction();
        current_byte++;
    }
}

// Contract
// PreCondition: current_byte is set to the beginning of next instruction
// PostCondition: current_byte is set to the end of produced instruction
void decaf::ByteCodeVisitor::produce_instruction() {
    using Instruction = ByteCode::Instruction;
    switch (*current_byte) {
        // No Operands
        case Instruction ::PLUS:
            op_PLUS();
            break;
        case Instruction ::MINUS:
            op_MINUS();
            break;
        case Instruction ::MULTIPLY:
            op_MULTIPLY();
            break;
        case Instruction ::DIVIDE:
            op_DIVIDE();
            break;

            // 0 Operand
        case Instruction ::GET_INSTANT:
            check_expected_byte(1);
            op_GET_INSTANT(*(current_byte++));
            break;
    }
}
bool decaf::ByteCodeVisitor::check_expected_byte(int count) {
    return count <= std::distance(current_byte, code_stream.end());
}
