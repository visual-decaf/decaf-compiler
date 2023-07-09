#include "program.h"

std::ostream& operator<<(std::ostream& os, const decaf::Program& prog) {
    os << "{ code = 0x{" << prog.code << "} }";
    return os;
}

decaf::IntConstantPool::index_type decaf::Program::add_int_constant(const int& val) {
    return i_pool.add_constant(val);
}
