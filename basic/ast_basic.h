#pragma once

#include <memory>

namespace decaf {
struct Type;
}

namespace decaf::ast {
struct Expr;
struct ArithmeticUnary;
struct ArithmeticBinary;
struct IntConstant;
struct Group;
struct LogicBinary;
struct LogicUnary;
struct BoolConstant;
struct RationalBinary;
struct EqualityBinary;
struct FloatConstant;
struct IdentifierExpr;
struct AssignExpr;
struct StringConstant;

struct Stmt;
struct ExpressionStmt;
struct ExpressionList;
struct PrintStmt;
using TypePtr = std::shared_ptr<decaf::Type>;
struct VariableDecl;
struct IfStmt;
} // namespace decaf::ast