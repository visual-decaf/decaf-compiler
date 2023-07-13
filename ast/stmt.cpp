#include "stmt.h"

bool decaf::ast::ExpressionStmt::equal(std::shared_ptr<Stmt> rhs) {
    auto stmt = std::dynamic_pointer_cast<ExpressionStmt>(rhs);

    if (!stmt) {
        return false;
    }

    return this->expr->equals(stmt->expr);
}
