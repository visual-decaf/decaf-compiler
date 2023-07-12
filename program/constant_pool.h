#pragma once

#include "serializable.h"
#include <cstddef>
#include <iostream>
#include <vector>

namespace decaf {
class ConstantPool;
}

std::ostream& operator<<(std::ostream& os, const decaf::ConstantPool&);

namespace decaf {

class ConstantPool: public Serializable {
    friend std::ostream& ::operator<<(std::ostream& os, const decaf::ConstantPool&);

public:
    using index_type = size_t;
    ConstantPool() = default;
    ConstantPool(std::initializer_list<int> list):
        i_pool(list) {
    }

    index_type add_constant(const int& val);
    int get_int_constant(index_type index);
    index_type add_constant(const double& val);
    double get_double_constant(index_type index);

    bool operator==(const ConstantPool& rhs) {
        return i_pool == rhs.i_pool;
    }

    boost::json::value to_json() override;

private:
    std::vector<int> i_pool;
    std::vector<double> f_pool;
};

} // namespace decaf