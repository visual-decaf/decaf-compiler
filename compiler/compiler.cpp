#include "compiler.h"
#include <map>
#include <stdexcept>
#include <unordered_map>

std::any decaf::Compiler::visitArithmeticBinary(decaf::ast::ArithmeticBinary* binary) {
    // Push lhs and rhs first into the stack
    binary->left->accept(*this);
    binary->right->accept(*this);

    // Finally put instruction for this operation
    using Operation = ast::ArithmeticBinary::Operation;
    using Instruction = ByteCode::Instruction;
    static std::map<Operation, ByteCode::code_type> code_for{
        {Operation ::PLUS, Instruction ::PLUS},
        {Operation ::MINUS, Instruction ::MINUS},
        {Operation ::MULTIPLY, Instruction ::MULTIPLY},
        {Operation ::DIVIDE, Instruction ::DIVIDE}};

    prog.emit(code_for[binary->op]);
    return {};
}

std::any decaf::Compiler::visitIntConstant(decaf::ast::IntConstant* constant) {
    if (constant->value > UINT8_MAX) {
        throw std::runtime_error{"Int too large for IntConstant"};
    }
    prog.emit_bytes(
        ByteCode::Instruction::GET_INSTANT,
        constant->value);
    return {};
}

void decaf::Compiler::compile() {
    ast_root->accept(*this);
}

decaf::Program decaf::Compiler::get_program() {
    return prog;
}