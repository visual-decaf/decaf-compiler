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

%nterm <decaf::ast::Expr*> expression
%nterm <decaf::ast::Expr*> arithmeticBinaryExpr
%nterm <decaf::ast::Expr*> intConstant
%nterm <decaf::ast::Expr*> group

%token <int> INTEGER
%token <int> HEX_INTEGER
%token PLUS '+' MINUS '-'
%token STAR '*' SLASH '/' PERCENT '%'
%token LEFT_PAREN '(' RIGHT_PAREN ')'
%token EOL

/* Expressions */
%left PLUS MINUS
%left STAR SLASH PERCENT

%%

input: 
    %empty
    | input expression EOL {
        driver.ast_root = $2;
    }
    ;

expression:
    arithmeticBinaryExpr
    | group
    | intConstant
    ;

arithmeticBinaryExpr: 
    expression PLUS expression {
        $$ = new ArithmeticBinary (
            $1,
            ArithmeticBinary::Operation::PLUS,
            $3
        );
    }
    | expression MINUS expression {
        $$ = new ArithmeticBinary (
            $1,
            ArithmeticBinary::Operation::MINUS,
            $3
        );
    }
    | expression STAR expression {
        $$ = new ArithmeticBinary (
            $1,
            ArithmeticBinary::Operation::MULTIPLY,
            $3
        );
    }
    | expression SLASH expression {
        $$ = new ArithmeticBinary (
            $1,
            ArithmeticBinary::Operation::DIVIDE,
            $3
        );
    }
    | expression PERCENT expression {
        $$ = new ArithmeticBinary (
            $1,
            ArithmeticBinary::Operation::MOD,
            $3
        );
    }

group:
    LEFT_PAREN expression RIGHT_PAREN {
        $$ = new Group {
            $2
        };
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
