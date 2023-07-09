#pragma once

#include <cstddef>
#include <vector>

namespace decaf {

template<typename T>
class BasicConstantPool {
public:
    using index_type = size_t;
    virtual index_type add_constant(const T&) = 0;
    virtual T get_constant(index_type) = 0;
};

class IntConstantPool:
    public BasicConstantPool<int> {
public:
    index_type add_constant(const int& val) override;
    int get_constant(index_type index) override;

private:
    std::vector<int> pool;
};

} // namespace decaf