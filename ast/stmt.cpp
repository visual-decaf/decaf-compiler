#include "stmt.h"

bool decaf::ast::ExpressionStmt::equal(std::shared_ptr<Stmt> rhs) {
    auto stmt = std::dynamic_pointer_cast<ExpressionStmt>(rhs);

    if (!stmt) {
        return false;
    }

    return this->expr->equals(stmt->expr);
}

boost::json::value decaf::ast::ExpressionStmt::to_json() {
    boost::json::object result{
        {"type", "ExpressionStmt"},
        {"expr", this->expr->to_json()}};
    return result;
}
