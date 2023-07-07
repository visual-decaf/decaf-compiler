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

%nterm <std::shared_ptr<decaf::ast::Expr>> arithmeticBinaryExpr
%nterm <std::shared_ptr<decaf::ast::IntConstant>> intConstant

%token <int> INTEGER
%token <int> HEX_INTEGER
%token PLUS '+' MINUS '-'
%token STAR '*' SLASH '/'
%token EOL

/* Expressions */
%left PLUS MINUS
%left STAR SLASH

%%

input: 
    %empty
    | input arithmeticBinaryExpr EOL
    ;

arithmeticBinaryExpr: 
    intConstant {
        $$ = $1;
    }
    | arithmeticBinaryExpr PLUS arithmeticBinaryExpr {
        $$ = make_shared<ArithmeticBinary> (
            $1,
            ArithmeticBinary::Operation::PLUS,
            $3
        );
    }
    | arithmeticBinaryExpr MINUS arithmeticBinaryExpr {
        $$ = make_shared<ArithmeticBinary> (
            $1,
            ArithmeticBinary::Operation::MINUS,
            $3
        );
    }
    | arithmeticBinaryExpr STAR arithmeticBinaryExpr {
        $$ = make_shared<ArithmeticBinary> (
            $1,
            ArithmeticBinary::Operation::MULTIPLY,
            $3
        );
    }
    | arithmeticBinaryExpr SLASH arithmeticBinaryExpr {
        $$ = make_shared<ArithmeticBinary> (
            $1,
            ArithmeticBinary::Operation::DIVIDE,
            $3
        );
    }

intConstant:
    INTEGER {
        $$ = make_shared<IntConstant>($1);
    } |
    HEX_INTEGER {
        $$ = make_shared<IntConstant>($1);
    }

%%

void yy::parser::error(const std::string& msg) {
    std::cerr << msg << '\n';
}