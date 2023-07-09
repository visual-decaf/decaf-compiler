#include "constant_pool.h"


decaf::IntConstantPool::index_type decaf::IntConstantPool::add_constant(const int& val) {
    // TODO: O(n) here, however there's not so many constant at all
    // Efficiency doesn't matter
    for (index_type i = 0; i < pool.size(); i++) {
        if (pool[i] == val) {
            return i;
        }
    }

    pool.push_back(val);
    return pool.size();
}

int decaf::IntConstantPool::get_constant(decaf::IntConstantPool::index_type index) {
    return pool[index];
}
