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
    list.emplace_back(boost::json::object{
        {"relation", "Value"},
        {"stmt", this->expr->to_json()}});
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
    boost::json::array expression_list;
    for (const auto& expression: this->list->expressions) {
        expression_list.emplace_back(boost::json::object{
            {"relation", ""},
            {"stmt", expression->to_json()}});
    }
    boost::json::object result{
        {"type", "PrintStmt"},
        {"name", "PrintStmt"},
        {"expression_list", expression_list},
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

bool decaf::ast::VariableDecl::equal(std::shared_ptr<Stmt> rhs) {
    auto stmt = std::dynamic_pointer_cast<VariableDecl>(rhs);

    if (!stmt) {
        return false;
    }

    return *(this->type) == *(stmt->type) && this->name == stmt->name;
}
boost::json::value decaf::ast::VariableDecl::to_json() {
    boost::json::array list;
    list.emplace_back(
        boost::json::object{
            {"relation", "Type"},
            {"stmt", boost::json::object{
                         {"type", "Type"},
                         {"value", this->type->to_json()},
                         {"resultType", this->type->to_json()}}}});
    list.emplace_back(boost::json::object{
        {"relation", "Identifier"},
        {"stmt", boost::json::object{
                     {"type", "Identifier"},
                     {"value", this->name},
                     {"resultType", this->type->to_json()}}}});
    list.emplace_back(boost::json::object{
        {"relation", "Init"},
        {"stmt", this->init->to_json()}});
    boost::json::object result{
        {"type", "VariableDecl"},
        {"name", "VariableDecl"},
        {"list", list},
        {"resultType", this->type->to_json()}};
    return result;
}

boost::json::value decaf::ast::ExpressionList::to_json() {
    boost::json::array result;
    for (const auto& expr: this->expressions) {
        result.emplace_back(expr->to_json());
    }
    return result;
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
boost::json::value decaf::ast::IfStmt::to_json() {
    boost::json::array list;
    list.emplace_back(boost::json::object{
        {"relation", "Condition"},
        {"stmt", this->condition->to_json()}});
    list.emplace_back(boost::json::object{
        {"relation", "Then"},
        {"stmt", this->then_stmt->to_json()}});
    if (this->else_stmt != nullptr) {
        list.emplace_back(boost::json::object{
            {"relation", "Else"},
            {"stmt", this->else_stmt->to_json()}});
    }
    boost::json::object result{
        {"type", "IfStmt"},
        {"name", "IfStmt"},
        {"list", list},
        {"resultType", "VOID"}};
    return result;
}
