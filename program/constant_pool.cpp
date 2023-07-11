#include "constant_pool.h"


decaf::ConstantPool::index_type decaf::ConstantPool::add_constant(const int& val) {
    // TODO: O(n) here, however there's not so many constant at all
    // Efficiency doesn't matter
    for (index_type i = 0; i < pool.size(); i++) {
        if (pool[i] == val) {
            return i;
        }
    }

    pool.push_back(val);
    return pool.size() - 1;
}

int decaf::ConstantPool::get_int_constant(index_type index) {
    return pool[index];
}

std::ostream& operator<<(std::ostream& os, const decaf::ConstantPool& i_pool) {
    for (decaf::ConstantPool::index_type i = 0; i < i_pool.pool.size(); i++) {
        os << "[" << i << "] = " << i_pool.pool[i] << ',';
    }
    return os;
}
