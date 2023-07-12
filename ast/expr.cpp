#include "expr.h"

const std::map<decaf::ast::ArithmeticUnary::Operation, std::string> decaf::ast::ArithmeticUnary::operation_name_of{
    {Operation::NEGATE, "NEGATE"}};

const std::map<decaf::ast::ArithmeticBinary::Operation, std::string> decaf::ast::ArithmeticBinary::operation_name_of{
    {Operation::PLUS, "PLUS"},
    {Operation::MINUS, "MINUS"},
    {Operation::MULTIPLY, "MULTIPLY"},
    {Operation::DIVIDE, "DIVIDE"},
    {Operation::MOD, "MOD"}};

const std::map<decaf::ast::LogicUnary::Operation, std::string> decaf::ast::LogicUnary::operation_name_of{
    {Operation::LOGIC_NOT, "LOGIC_NOT"}};

const std::map<decaf::ast::LogicBinary::Operation, std::string> decaf::ast::LogicBinary::operation_name_of{
    {Operation::LOGIC_AND, "LOGIC_AND"},
    {Operation::LOGIC_OR, "LOGIC_OR"}};

const std::map<decaf::ast::RationalBinary::Operation, std::string> decaf::ast::RationalBinary::operation_name_of{
    {Operation::GREATER, "GREATER"},
    {Operation::GREATER_EQUAL, "GREATER_EQUAL"},
    {Operation::LESS, "LESS"},
    {Operation::LESS_EQUAL, "LESS_EQUAL"}};

bool decaf::ast::ArithmeticBinary::equals(std::shared_ptr<Expr> ptr) {
    auto arith = std::dynamic_pointer_cast<ArithmeticBinary>(ptr);

    // Not the same type
    if (arith == nullptr) {
        return false;
    }

    return this->op == arith->op && this->left->equals(arith->left) && this->right->equals(arith->right);
}

boost::json::value decaf::ast::ArithmeticBinary::to_json() {
    boost::json::object result{
        {"type", "ArithmeticBinary"},
        {"operation", operation_name_of.at(this->op)},
        {"left", this->left->to_json()},
        {"right", this->right->to_json()},
        {"resultType", this->type.to_json()}};
    return result;
}

decaf::Type::Classification decaf::ast::ArithmeticBinary::result_type_of(decaf::Type left, decaf::Type right) {
    if (left.classification == Type::Classification::INT
        && right.classification == Type::Classification::INT) {
        return Type::Classification::INT;
    }
    if (left.classification == Type::Classification::FLOAT
        && right.classification == Type::Classification::FLOAT) {
        return Type::Classification::FLOAT;
    }
    return Type::Classification::INVALID;
}

bool decaf::ast::IntConstant::equals(std::shared_ptr<Expr> ptr) {
    auto val = std::dynamic_pointer_cast<IntConstant>(ptr);

    if (val == nullptr) {
        return false;
    }

    return this->value == val->value;
}

boost::json::value decaf::ast::IntConstant::to_json() {
    boost::json::value result = {
        {"type", "IntConstant"},
        {"value", this->value},
        {"resultType", this->type.to_json()}};
    return result;
}

bool decaf::ast::Group::equals(std::shared_ptr<Expr> ptr) {
    auto group = std::dynamic_pointer_cast<Group>(ptr);

    if (group == nullptr) {
        return false;
    }

    if (this->content == nullptr) {
        return group->content == nullptr;
    }

    return this->content->equals(group->content);
}

boost::json::value decaf::ast::Group::to_json() {
    boost::json::object result{
        {"type", "Group"},
    };
    if (this->content == nullptr) {
        result["content"] = boost::json::object{
            {"type", "INVALID"},
            {"resultType", "INVALID"}};
    } else {
        result["content"] = this->content->to_json();
    }
    result["resultType"] = this->type.to_json();
    return result;
}

bool decaf::ast::LogicBinary::equals(std::shared_ptr<Expr> ptr) {
    auto log = std::dynamic_pointer_cast<LogicBinary>(ptr);

    if (log == nullptr) {
        return false;
    }

    return this->left->equals(log->left) && this->right->equals(log->right);
}

decaf::Type::Classification decaf::ast::LogicBinary::result_type_of(decaf::Type left, decaf::Type right) {
    if (left.classification == Type::Classification::BOOL && right.classification == Type::Classification::BOOL) {
        return Type::Classification::BOOL;
    }

    return Type::Classification::INVALID;
}
boost::json::value decaf::ast::LogicBinary::to_json() {
    boost::json::object result{
        {"type", "LogicBinary"},
        {"operation", operation_name_of.at(this->op)},
        {"left", this->left->to_json()},
        {"right", this->right->to_json()},
        {"resultType", this->type.to_json()}};
    return result;
}

bool decaf::ast::BoolConstant::equals(std::shared_ptr<Expr> ptr) {
    auto rhs = std::dynamic_pointer_cast<BoolConstant>(ptr);

    if (rhs == nullptr) {
        return false;
    }

    return this->value == rhs->value;
}
boost::json::value decaf::ast::BoolConstant::to_json() {
    boost::json::value result{
        {"type", "BoolConstant"},
        {"value", this->value},
        {"resultType", this->type.to_json()}};
    return result;
}

decaf::Type::Classification decaf::ast::ArithmeticUnary::result_type_of(decaf::Type right) {
    if (right.classification == Type::Classification::INT)
        return Type::Classification::INT;
    return Type::Classification::INVALID;
}
boost::json::value decaf::ast::ArithmeticUnary::to_json() {
    boost::json::object result{
        {"type", "ArithmeticUnary"},
        {"operation", operation_name_of.at(this->op)},
        {"right", this->right->to_json()},
        {"resultType", this->type.to_json()}};
    return result;
}

bool decaf::ast::ArithmeticUnary::equals(std::shared_ptr<Expr> ptr) {
    auto rhs = std::dynamic_pointer_cast<ArithmeticUnary>(ptr);

    if (rhs == nullptr) {
        return false;
    }

    return this->right->equals(rhs->right);
}

bool decaf::ast::LogicUnary::equals(std::shared_ptr<Expr> ptr) {
    auto rhs = std::dynamic_pointer_cast<LogicUnary>(ptr);

    if (rhs == nullptr) {
        return false;
    }

    return this->right->equals(rhs->right);
}

decaf::Type::Classification decaf::ast::LogicUnary::result_type_of(decaf::Type right) {
    if (right.classification == Type::Classification::BOOL) {
        return Type::Classification::BOOL;
    }

    return Type::Classification::INVALID;
}
boost::json::value decaf::ast::LogicUnary::to_json() {
    boost::json::object result{
        {"type", "LogicUnary"},
        {"operation", operation_name_of.at(this->op)},
        {"right", this->right->to_json()},
        {"resultType", this->type.to_json()}};
    return result;
}

decaf::Type::Classification decaf::ast::RationalBinary::result_type_of(decaf::Type left, decaf::Type right) {
    if (left.classification == Type::Classification::INT && right.classification == Type::Classification::INT) {
        return Type::Classification::BOOL;
    }

    return Type::Classification::INVALID;
}

bool decaf::ast::RationalBinary::equals(std::shared_ptr<Expr> rational_bin) {
    auto rhs = std::dynamic_pointer_cast<RationalBinary>(rational_bin);

    if (rhs == nullptr) {
        return false;
    }

    return this->left->equals(rhs->left)
           && this->op == rhs->op
           && this->right->equals(rhs->right);
}
boost::json::value decaf::ast::RationalBinary::to_json() {
    boost::json::object result{
        {"type", "RationalBinary"},
        {"operation", operation_name_of.at(this->op)},
        {"left", this->left->to_json()},
        {"right", this->right->to_json()},
        {"resultType", this->type.to_json()}};
    return result;
}

bool decaf::ast::EqualityBinary::equals(std::shared_ptr<Expr> ptr) {
    auto rhs = std::dynamic_pointer_cast<EqualityBinary>(ptr);

    if (rhs == nullptr) {
        return false;
    }

    return this->left->equals(rhs->left)
           && this->op == rhs->op
           && this->right->equals(rhs->right);
}

decaf::Type::Classification decaf::ast::EqualityBinary::result_type_of(decaf::Type left, decaf::Type right) {
    if (left.classification == right.classification && left.classification != Type::Classification::INVALID) {
        return Type::Classification::BOOL;
    }
    return Type::Classification::INVALID;
}

bool decaf::ast::FloatConstant::equals(std::shared_ptr<Expr> ptr) {
    auto rhs = std::dynamic_pointer_cast<FloatConstant>(ptr);

    if (rhs == nullptr) {
        return false;
    }

    return this->value == rhs->value;
}
