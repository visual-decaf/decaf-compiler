#include "program.h"

std::ostream& operator<<(std::ostream& os, const decaf::Program& prog) {
    os << "{ code = 0x{" << prog.code << "}\n";
    os << "Constant = [" << prog.pool << "] }";
    return os;
}

decaf::ConstantPool::index_type decaf::Program::add_int_constant(const int& val) {
    return pool.add_constant(val);
}

void decaf::Program::set_result_type(const decaf::Type& result) {
    result_type = result;
}

void decaf::Program::set_result_type_classification(const decaf::Type::Classification& classification) {
    result_type.classification = classification;
}

decaf::Type decaf::Program::get_result_type() const {
    return result_type;
}

decaf::Type::Classification decaf::Program::get_result_type_classification() const {
    return result_type.classification;
}

boost::json::value decaf::Program::to_json() {
    boost::json::object result{
        {"bytecode", this->code.to_json()},
        {"resultType", this->result_type.to_json()},
        {"constantPool", this->pool.to_json()}};
    return result;
}

decaf::ConstantPool::index_type decaf::Program::add_double_constant(const double& val) {
    return pool.add_constant(val);
}

decaf::ConstantPool::index_type decaf::Program::add_string_constant(const std::string& val) {
    return pool.add_constant(val);
}
