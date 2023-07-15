#include "stmt.h"

bool decaf::ast::ExpressionStmt::equal(std::shared_ptr<Stmt> rhs) {
    auto stmt = std::dynamic_pointer_cast<ExpressionStmt>(rhs);

    if (!stmt) {
        return false;
    }

    return this->expr->equals(stmt->expr);
}

boost::json::value decaf::ast::ExpressionStmt::to_json() {
    boost::json::array list;
    list.emplace_back(this->expr->to_json());
    boost::json::object result{
        {"type", "ExpressionStmt"},
        {"name", "ExpressionStmt"},
        {"list", list},
        {"resultType", "VOID"}};
    return result;
}

bool decaf::ast::PrintStmt::equal(std::shared_ptr<Stmt> rhs) {
    auto stmt = std::dynamic_pointer_cast<PrintStmt>(rhs);

    if (!stmt) {
        return false;
    }

    return list->equal(*stmt->list);
}
boost::json::value decaf::ast::PrintStmt::to_json() {
    boost::json::object result{
        {"type", "PrintStmt"},
        {"name", "PrintStmt"},
        {"list", this->list->to_json()},
        {"resultType", "VOID"}};
    return result;
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

boost::json::value decaf::ast::ExpressionList::to_json() {
    boost::json::array result;
    for (const auto& expr: this->expressions) {
        result.emplace_back(expr->to_json());
    }
    return result;
}
