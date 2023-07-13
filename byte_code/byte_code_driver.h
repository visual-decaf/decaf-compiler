#include "byte_code.h"
#include "byte_code_visitor.h"

namespace decaf {

class ByteCodeDriver {
public:
    explicit ByteCodeDriver(ByteCode& code, ByteCodeVisitor& visitor):
        code{code}, visitor{visitor} {
    }

    virtual bool produce();
    using code_stream_type = ByteCode::code_stream_type;
    using iterator_type = code_stream_type::iterator;

private:
    bool produce_instruction();
    bool check_expected_byte(int count);

    ByteCode& code;
    ByteCodeVisitor& visitor;
    code_stream_type& code_stream = code.code_stream;
    iterator_type current_byte = code_stream.begin();
};

} // namespace decaf