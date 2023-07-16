#include "byte_code.h"
#include "debug_vm.h"
#include "program.h"
#include "visual_decaf.h"
#include <iostream>
using namespace decaf;
int main() {
    auto input_prog = Program{
        ByteCode{
            ByteCode::Instruction ::GET_INSTANT,
            0,
            ByteCode::Instruction ::SYMBOL_ADD,
            0,
            ByteCode::Instruction ::SYMBOL_GET,
            0,
            ByteCode::Instruction ::GET_INSTANT,
            1,
            ByteCode::Instruction ::SYMBOL_SET,
            ByteCode::Instruction ::DISCARD,
            ByteCode::Instruction ::SYMBOL_GET,
            0,
            ByteCode::Instruction ::PRINT,
            1,
        }};
    input_prog.set_result_type_classification(Type::Classification::VOID);
    DebugVirtualMachine debugVirtualMachine{input_prog};
    debugVirtualMachine.run();
    const std::vector<ExeResult>& vector = debugVirtualMachine.get_exe_results();
    boost::json::array list;
    for (ExeResult exeResult: vector) {
        list.emplace_back(exeResult.to_json());
    }
    std::cout << boost::json::serialize(list) << std::endl;
}