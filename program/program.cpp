#include "program.h"

std::ostream& operator<<(std::ostream& os, const decaf::Program& prog) {
    os << "{ code = 0x{" << prog.code << "}\n";
    os << "  Int Constant = [" << prog.i_pool << "] }";
    return os;
}

decaf::IntConstantPool::index_type decaf::Program::add_int_constant(const int& val) {
    return i_pool.add_constant(val);
}

void decaf::Program::set_result_type(const decaf::Type& result) {
    result_type = result;
}

void decaf::Program::set_result_type_classification(const decaf::Type::Classification& classification) {
    result_type.classification = classification;
}

boost::json::value decaf::Program::to_json() {
    boost::json::object result{
        {"bytecode", this->code.to_json()},
        {"intConstantPool", this->i_pool.to_json()}};
    return result;
}
