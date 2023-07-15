#include "byte_code_driver.h"

bool decaf::ByteCodeDriver::produce() {
    while (current_byte != code_stream.end()) {
        bool success = produce_instruction();
        if (!success)
            return false;
        current_byte++;
    }
    return true;
}

// Contract
// PreCondition: current_byte is set to the beginning of next instruction
// PostCondition: current_byte is set to the end of produced instruction
bool decaf::ByteCodeDriver::produce_instruction() {
    using Instruction = ByteCode::Instruction;
    switch (*current_byte) {
            // No Operands
        case Instruction ::PLUS:
            return visitor.op_PLUS();
        case Instruction ::MINUS:
            return visitor.op_MINUS();
        case Instruction ::MULTIPLY:
            return visitor.op_MULTIPLY();
        case Instruction ::DIVIDE:
            return visitor.op_DIVIDE();
        case Instruction ::MOD:
            return visitor.op_MOD();
        case Instruction ::NEGATE:
            return visitor.op_NEGATE();
        case Instruction ::LOGIC_NOT:
            return visitor.op_LOGIC_NOT();
        case Instruction ::GET_TRUE:
            return visitor.op_GET_TRUE();
        case Instruction ::GET_FALSE:
            return visitor.op_GET_FALSE();
        case Instruction ::LOGIC_AND:
            return visitor.op_LOGIC_AND();
        case Instruction ::LOGIC_OR:
            return visitor.op_LOGIC_OR();
        case Instruction ::LESS:
            return visitor.op_LESS();
        case Instruction ::LESS_EQUAL:
            return visitor.op_LESS_EQUAL();
        case Instruction ::GREATER:
            return visitor.op_GREATER();
        case Instruction ::GREATER_EQUAL:
            return visitor.op_GREATER_EQUAL();
        case Instruction ::EQUAL:
            return visitor.op_EQUAL();
        case Instruction ::NOT_EQUAL:
            return visitor.op_NOT_EQUAL();
        case Instruction ::DISCARD:
            return visitor.op_DISCARD();
        case Instruction ::SYMBOL_SET:
            return visitor.op_SYMBOL_SET();

            // 1 Operand
        case Instruction ::GET_INSTANT:
            check_expected_byte(1);
            return visitor.op_GET_INSTANT(*(++current_byte));
        case Instruction ::GET_INT_CONSTANT:
            check_expected_byte(1);
            return visitor.op_GET_INT_CONSTANT(*(++current_byte));
        case Instruction ::GET_FLOAT_CONSTANT:
            check_expected_byte(1);
            return visitor.op_GET_FLOAT_CONSTANT(*(++current_byte));
        case Instruction ::PRINT:
            check_expected_byte(1);
            return visitor.op_PRINT(*(++current_byte));
        case Instruction ::SYMBOL_ADD:
            check_expected_byte(1);
            return visitor.op_SYMBOL_ADD(*(++current_byte));
        case Instruction ::SYMBOL_GET:
            check_expected_byte(1);
            return visitor.op_SYMBOL_GET(*(++current_byte));
    }

    // No such Instruction
    return false;
}

bool decaf::ByteCodeDriver::check_expected_byte(int count) {
    return count <= std::distance(current_byte, code_stream.end());
}
