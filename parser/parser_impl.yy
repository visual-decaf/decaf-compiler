%language "C++"
%define api.value.type variant
/* %define api.token.constructor */
%define parse.error verbose
%define parse.trace

%param{decaf::Parser& driver}

%code requires {
    #include <memory>
    #include "ast_basic.h"
    #include "parser_basic.h"
}

%code top {
    #include "expr.h"
    #include "parser.h"
    using namespace std;
    using namespace decaf::ast;
}

%nterm <decaf::ast::Expr*> arithmeticBinaryExpr
%nterm <decaf::ast::IntConstant*> intConstant

%token <int> INTEGER
%token <int> HEX_INTEGER
%token PLUS '+' MINUS '-'
%token STAR '*' SLASH '/' PERCENT '%'
%token EOL

/* Expressions */
%left PLUS MINUS
%left STAR SLASH PERCENT

%%

input: 
    %empty
    | input arithmeticBinaryExpr EOL {
        driver.ast_root = $2;
    }
    ;

arithmeticBinaryExpr: 
    intConstant {
        $$ = $1;
    }
    | arithmeticBinaryExpr PLUS arithmeticBinaryExpr {
        $$ = new ArithmeticBinary (
            $1,
            ArithmeticBinary::Operation::PLUS,
            $3
        );
    }
    | arithmeticBinaryExpr MINUS arithmeticBinaryExpr {
        $$ = new ArithmeticBinary (
            $1,
            ArithmeticBinary::Operation::MINUS,
            $3
        );
    }
    | arithmeticBinaryExpr STAR arithmeticBinaryExpr {
        $$ = new ArithmeticBinary (
            $1,
            ArithmeticBinary::Operation::MULTIPLY,
            $3
        );
    }
    | arithmeticBinaryExpr SLASH arithmeticBinaryExpr {
        $$ = new ArithmeticBinary (
            $1,
            ArithmeticBinary::Operation::DIVIDE,
            $3
        );
    }
    | arithmeticBinaryExpr PERCENT arithmeticBinaryExpr {
        $$ = new ArithmeticBinary (
            $1,
            ArithmeticBinary::Operation::MOD,
            $3
        );
    }

intConstant:
    INTEGER {
        $$ = new IntConstant($1);
    } |
    HEX_INTEGER {
        $$ = new IntConstant($1);
    }

%%

void yy::parser::error(const std::string& msg) {
    std::cerr << msg << '\n';
}
