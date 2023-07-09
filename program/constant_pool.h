#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

namespace decaf {
class IntConstantPool;
}

std::ostream& operator<<(std::ostream& os, const decaf::IntConstantPool&);

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
    friend std::ostream& ::operator<<(std::ostream& os, const decaf::IntConstantPool&);

public:
    index_type add_constant(const int& val) override;
    int get_constant(index_type index) override;

    bool operator==(const IntConstantPool& rhs) {
        return pool == rhs.pool;
    }

private:
    std::vector<int> pool;
};

} // namespace decaf