#include "vm.h"

#include "exe_result.h"
#include <utility>

namespace decaf {

class DebugVirtualMachine: ByteCodeVisitor {
    explicit DebugVirtualMachine(Program program):
        vm{std::move(program)} {
    }

    bool op_PLUS() override;
    bool op_GET_INSTANT(uint8_t instant) override;

    std::vector<ExeResult> get_exe_results();

private:
    VirtualMachine vm;
    std::vector<ExeResult> exe_results;
};

}; // namespace decaf