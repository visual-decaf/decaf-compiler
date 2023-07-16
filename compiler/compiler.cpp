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
    for (auto&& stmt: statements) {
        stmt->accept(*this);
    }
    prog.set_result_type_classification(Type::Classification::VOID);
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

std::any decaf::Compiler::visitEqualityBinary(std::shared_ptr<ast::EqualityBinary> equal_bin) {
    equal_bin->left->accept(*this);
    equal_bin->right->accept(*this);

    using Operation = ast::EqualityBinary::Operation;
    using Instruction = ByteCode::Instruction;
    static std::map<Operation, ByteCode::code_type> code_for{
        {Operation ::EQUAL, Instruction ::EQUAL},
        {Operation ::NOT_EQUAL, Instruction ::NOT_EQUAL}};

    prog.emit(code_for[equal_bin->op]);
    return {};
}

std::any decaf::Compiler::visitFloatConstant(std::shared_ptr<ast::FloatConstant> floatConstant) {
    ConstantPool::index_type index = prog.add_double_constant(floatConstant->value);
    prog.emit_bytes(
        ByteCode::Instruction::GET_FLOAT_CONSTANT,
        index);
    return {};
}

std::any decaf::Compiler::visitExpressionStmt(std::shared_ptr<ast::ExpressionStmt> expressionStmt) {
    expressionStmt->expr->accept(*this);
    prog.emit(ByteCode::Instruction::DISCARD);
    return {};
}

std::any decaf::Compiler::visitPrintStmt(std::shared_ptr<ast::PrintStmt> printStmt) {
    auto& expressions = printStmt->list->expressions;
    for (auto it = expressions.rbegin(); it != expressions.rend(); it++) {
        auto expr = *it;
        expr->accept(*this);
    }
    prog.emit_bytes(
        ByteCode::Instruction::PRINT,
        printStmt->list->expressions.size());
    return {};
}

bool decaf::Compiler::emit_code_for_default(decaf::Type type) {
    if (type.classification == decaf::Type::Classification::INT) {
        prog.emit_bytes(
            ByteCode::Instruction::GET_INSTANT,
            0);
        return true;
    } else if (type.classification == decaf::Type::Classification::BOOL) {
        prog.emit(ByteCode::Instruction::GET_FALSE);
        return true;
    } else if (type.classification == decaf::Type::Classification::FLOAT) {
        prog.emit(ByteCode::Instruction::GET_FLOAT_ZERO);
        return true;
    }
    return false;
}

std::any decaf::Compiler::visitVariableDecl(std::shared_ptr<ast::VariableDecl> variableDecl) {
    symbol_index_of[variableDecl->name] = index_count++;
    symbol_declaration_of[variableDecl->name] = variableDecl;
    if (variableDecl->init == nullptr) {
        emit_code_for_default(*variableDecl->type);
    } else {
        variableDecl->init->accept(*this);
    }
    prog.emit_bytes(
        ByteCode::Instruction::SYMBOL_ADD,
        symbol_index_of[variableDecl->name]);
    return {};
}

std::any decaf::Compiler::visitIdentifierExpr(std::shared_ptr<ast::IdentifierExpr> identifierExpr) {
    identifierExpr->index = symbol_index_of[identifierExpr->name];
    identifierExpr->type = *symbol_declaration_of[identifierExpr->name]->type;
    prog.emit_bytes(
        ByteCode::Instruction::SYMBOL_GET,
        symbol_index_of[identifierExpr->name]);
    return {};
}

std::any decaf::Compiler::visitAssignExpr(std::shared_ptr<ast::AssignExpr> assignExpr) {
    auto lhs = std::dynamic_pointer_cast<ast::LValue>(assignExpr->left);
    assignExpr->left->accept(*this);
    assignExpr->right->accept(*this);

    if (assignExpr->right->type != lhs->type) {
        throw std::runtime_error("Assign with wrong type");
    }

    prog.emit(ByteCode::Instruction::SYMBOL_SET);
    return {};
}

std::any decaf::Compiler::visitStringConstant(std::shared_ptr<ast::StringConstant> stringConstant) {
    ConstantPool::index_type index = prog.add_string_constant(stringConstant->value);
    prog.emit_bytes(
        ByteCode::Instruction::GET_STRING_CONSTANT,
        index);
    return {};
}
