#include "program.h"

std::ostream& operator<<(std::ostream& os, const decaf::Program& prog) {
    os << "{ code = 0x{" << prog.code << "}\n";
    os << "  Int Constant = [" << prog.pool << "] }";
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
