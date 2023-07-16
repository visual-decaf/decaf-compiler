#include "constant_pool.h"


decaf::ConstantPool::index_type decaf::ConstantPool::add_constant(const int& val) {
    // TODO: O(n) here, however there's not so many constant at all
    // Efficiency doesn't matter
    for (index_type i = 0; i < i_pool.size(); i++) {
        if (i_pool[i] == val) {
            return i;
        }
    }

    i_pool.push_back(val);
    return i_pool.size() - 1;
}

int decaf::ConstantPool::get_int_constant(index_type index) {
    return i_pool[index];
}

std::ostream& operator<<(std::ostream& os, const decaf::ConstantPool& i_pool) {
    for (decaf::ConstantPool::index_type i = 0; i < i_pool.i_pool.size(); i++) {
        os << "[" << i << "] = " << i_pool.i_pool[i] << ',';
    }
    return os;
}

boost::json::value decaf::ConstantPool::to_json() {
    boost::json::object result;
    boost::json::array int_constant_pool;
    boost::json::array double_constant_pool;
    for (auto constant: this->i_pool) {
        int_constant_pool.emplace_back(constant);
    }
    result["intConstantPool"] = int_constant_pool;
    result["doubleConstantPool"] = double_constant_pool;
    return result;
}

decaf::ConstantPool::index_type decaf::ConstantPool::add_constant(const double& val) {
    for (index_type i = 0; i < f_pool.size(); i++) {
        if (std::fabs(val - f_pool[i]) < 1e-10) {
            return i;
        }
    }

    f_pool.push_back(val);
    return f_pool.size() - 1;
}

double decaf::ConstantPool::get_double_constant(decaf::ConstantPool::index_type index) {
    return f_pool[index];
}

decaf::ConstantPool::index_type decaf::ConstantPool::add_constant(const std::string& val) {
    for (index_type i = 0; i < s_pool.size(); i++) {
        if (s_pool[i] == val) {
            return i;
        }
    }

    s_pool.push_back(val);
    return s_pool.size() - 1;
}

std::string decaf::ConstantPool::get_string_constant(decaf::ConstantPool::index_type index) {
    return s_pool[index];
}
