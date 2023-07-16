#include "debug_vm.h"
#include "program.h"
#include "visual_decaf.h"
#include <iostream>
using namespace decaf;
int main() {
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
    boost::json::array list;
    for (ExeResult exe: vector) {
        list.emplace_back(exe.to_json());
    }
    std::cout << boost::json::serialize(list) << std::endl;
}