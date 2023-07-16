#include "stmt.h"

bool decaf::ast::ExpressionStmt::equal(std::shared_ptr<Stmt> rhs) {
    auto stmt = std::dynamic_pointer_cast<ExpressionStmt>(rhs);

    if (!stmt) {
        return false;
    }

    return this->expr->equals(stmt->expr);
}

bool decaf::ast::PrintStmt::equal(std::shared_ptr<Stmt> rhs) {
    auto stmt = std::dynamic_pointer_cast<PrintStmt>(rhs);

    if (!stmt) {
        return false;
    }

    return list->equal(*stmt->list);
}

bool decaf::ast::ExpressionList::equal(const decaf::ast::ExpressionList& rhs) {
    if (expressions.size() != rhs.expressions.size()) {
        return false;
    }

    for (int i = 0; i < expressions.size(); i++) {
        if (!expressions[i]->equals(rhs.expressions[i])) {
            return false;
        }
    }

    return true;
}

bool decaf::ast::VariableDecl::equal(std::shared_ptr<Stmt> rhs) {
    auto stmt = std::dynamic_pointer_cast<VariableDecl>(rhs);

    if (!stmt) {
        return false;
    }

    return *(this->type) == *(stmt->type) && this->name == stmt->name;
}


bool decaf::ast::IfStmt::equal(std::shared_ptr<Stmt> rhs) {
    auto stmt = std::dynamic_pointer_cast<IfStmt>(rhs);

    if (!stmt) {
        return false;
    }

    if (this->else_stmt == nullptr) {
        return this->condition->equals(stmt->condition)
               && this->then_stmt->equal(stmt->then_stmt)
               && stmt->else_stmt == nullptr;
    } else {
        return this->condition->equals(stmt->condition)
               && this->then_stmt->equal(stmt->then_stmt)
               && stmt->else_stmt != nullptr
               && this->else_stmt->equal(stmt->else_stmt);
    }
}