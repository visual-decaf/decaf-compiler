#include "compiler.h"
#include <map>
#include <stdexcept>
#include <unordered_map>

std::any decaf::Compiler::visitArithmeticBinary(std::shared_ptr<decaf::ast::ArithmeticBinary> binary) {
    // Push lhs and rhs first into the stack
    binary->left->accept(*this);
    binary->right->accept(*this);

    // TODO: Add type check here

    // Finally put instruction for this operation
    using Operation = ast::ArithmeticBinary::Operation;
    using Instruction = ByteCode::Instruction;
    static std::map<Operation, ByteCode::code_type> code_for{
        {Operation ::PLUS, Instruction ::PLUS},
        {Operation ::MINUS, Instruction ::MINUS},
        {Operation ::MULTIPLY, Instruction ::MULTIPLY},
        {Operation ::DIVIDE, Instruction ::DIVIDE},
        {Operation ::MOD, Instruction ::MOD}};

    prog.emit(code_for[binary->op]);
    return {};
}

std::any decaf::Compiler::visitIntConstant(std::shared_ptr<decaf::ast::IntConstant> constant) {
    if (constant->value > UINT8_MAX) {
        IntConstantPool::index_type index = prog.add_int_constant(constant->value);
        prog.emit_bytes(
            ByteCode::Instruction::GET_INT_CONSTANT,
            index);
        return {};
    }
    prog.emit_bytes(
        ByteCode::Instruction::GET_INSTANT,
        constant->value);
    return {};
}

std::any decaf::Compiler::visitGroup(std::shared_ptr<ast::Group> group) {
    group->content->accept(*this);
    return {};
}

void decaf::Compiler::compile() {
    ast_root->accept(*this);
}

decaf::Program decaf::Compiler::get_program() {
    return prog;
}
