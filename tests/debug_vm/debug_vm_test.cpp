#include "byte_code.h"
#include "debug_vm.h"
#include "program.h"
#include <catch2/catch_test_macros.hpp>
using namespace decaf;

TEST_CASE("op_plus", "[debug_vm]") {
    auto input_prog = Program{
        ByteCode{
            decaf::ByteCode::Instruction ::GET_INSTANT,
            1,
            decaf::ByteCode::Instruction ::GET_INSTANT,
            2,
            decaf::ByteCode::Instruction ::PLUS,
        }};
    DebugVirtualMachine debugVirtualMachine{input_prog};
    debugVirtualMachine.run();
    const std::vector<ExeResult>& vector = debugVirtualMachine.get_exe_results();
}