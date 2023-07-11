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
        ConstantPool::index_type index = prog.add_int_constant(constant->value);
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

std::any decaf::Compiler::visitLogicBinary(std::shared_ptr<ast::LogicBinary> logicBinary) {
    logicBinary->left->accept(*this);
    logicBinary->right->accept(*this);

    using Operation = ast::LogicBinary::Operation;
    using Instruction = ByteCode::Instruction;
    static std::map<Operation, ByteCode::code_type> code_for{
        {Operation ::LOGIC_AND, Instruction ::LOGIC_AND},
        {Operation ::LOGIC_OR, Instruction ::LOGIC_OR},
    };
    prog.emit(code_for[logicBinary->op]);
    return {};
}

std::any decaf::Compiler::visitBoolConstant(std::shared_ptr<ast::BoolConstant> boolConstant) {
    using Instruction = ByteCode::Instruction;
    static std::map<bool, ByteCode::code_type> code_for{
        {true, Instruction ::GET_TRUE},
        {false, Instruction ::GET_FALSE},
    };
    prog.emit(code_for[boolConstant->value]);
    return {};
}

std::any decaf::Compiler::visitArithmeticUnary(std::shared_ptr<ast::ArithmeticUnary> ari_unary) {
    ari_unary->right->accept(*this);

    prog.emit(ByteCode::Instruction::NEGATE);
    return {};
}

void decaf::Compiler::compile() {
    ast_root->accept(*this);
    prog.set_result_type(ast_root->type);
}

decaf::Program decaf::Compiler::get_program() {
    return prog;
}

std::any decaf::Compiler::visitLogicUnary(std::shared_ptr<ast::LogicUnary> log_unary) {
    log_unary->right->accept(*this);

    prog.emit(ByteCode::Instruction::LOGIC_NOT);
    return {};
}

std::any decaf::Compiler::visitRationalBinary(std::shared_ptr<ast::RationalBinary> rational_bin) {
    rational_bin->left->accept(*this);
    rational_bin->right->accept(*this);

    using Operation = ast::RationalBinary::Operation;
    using Instruction = ByteCode::Instruction;
    static std::map<Operation, ByteCode::code_type> code_for{
        {Operation ::LESS, Instruction ::LESS},
        {Operation ::LESS_EQUAL, Instruction ::LESS_EQUAL},
        {Operation ::GREATER, Instruction ::GREATER},
        {Operation ::GREATER_EQUAL, Instruction ::GREATER_EQUAL},
    };

    prog.emit(code_for[rational_bin->op]);
    return {};
}
