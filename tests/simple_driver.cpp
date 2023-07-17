#include "byte_code.h"
#include "debug_vm.h"
#include "visual_decaf.h"
#include <iostream>
#include <streambuf>

using namespace decaf;
int main() {
    auto input_prog = Program(
        ByteCode{
            ByteCode::Instruction ::GET_INSTANT,
            1,
            ByteCode::Instruction ::GOTO,
            4, // jump to GET_FALSE
            ByteCode::Instruction ::GET_FALSE,
            ByteCode::Instruction ::GET_TRUE,
            ByteCode::Instruction ::PRINT,
            1,
            ByteCode::Instruction ::PRINT,
            1,
            ByteCode::Instruction ::GET_FALSE,
            ByteCode::Instruction ::GOTO_IF_FALSE,
            15,
            ByteCode::Instruction ::GET_FLOAT_ZERO,
            ByteCode::Instruction ::GET_TRUE,
            ByteCode::Instruction ::GET_FLOAT_ZERO,
            ByteCode::Instruction ::GET_INSTANT,
            7,
            ByteCode::Instruction ::GET_INSTANT,
            10,
            ByteCode::Instruction ::PLUS,
            ByteCode::Instruction ::PRINT,
            2});
    input_prog.set_result_type_classification(Type::Classification::VOID);
    DebugVirtualMachine debugVirtualMachine{input_prog};
    debugVirtualMachine.run();
    const std::vector<ExeResult>& vector = debugVirtualMachine.get_exe_results();
    boost::json::array list;
    for (ExeResult element: vector) {
        list.emplace_back(element.to_json());
    }
    std::cout << boost::json::serialize(list) << std::endl;
}