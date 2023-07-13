#pragma once

#include "ast_basic.h"
#include <any>
#include <memory>

namespace decaf {
struct StmtVisitor {
};
} // namespace decaf

namespace decaf::ast {

struct Stmt {
    virtual std::any accept(StmtVisitor& visitor) = 0;
    virtual bool equal(std::shared_ptr<Stmt> rhs) = 0;

    virtual ~Stmt() = default;
};

} // namespace decaf::ast
