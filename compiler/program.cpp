#include "program.h"

std::ostream& operator<<(std::ostream& os, const decaf::Program& prog) {
    os << "{ code = 0x{" << prog.code << "} }";
    return os;
}
