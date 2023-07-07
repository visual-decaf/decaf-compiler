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

%nterm <std::shared_ptr<decaf::ast::Expr>> expr
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
    | input expr EOL
    ;

expr: 
    intConstant {
        $$ = $1;
    }
    | expr PLUS expr {
        $$.left = $1;
        $$.op = ArithmeticBinary::Operation::PLUS;
        $$.right = $3;
    }
    | expr MINUS expr {
        $$.left = $1;
        $$.op = ArithmeticBinary::Operation::MINUS;
        $$.right = $3;
    }
    | expr STAR expr {
        $$.left = $1;
        $$.op = ArithmeticBinary::Operation::MULTIPLY;
        $$.right = $3;
    }
    | expr SLASH expr {
        $$.left = $1;
        $$.op = ArithmeticBinary::Operation::DIVIDE ;
        $$.right = $3;
    }

intConstant:
    INTEGER {
        $$.value = $1;
    } |
    HEX_INTEGER {
        $$.value = $1;
    }

%%

void yy::parser::error(const std::string& msg) {
    std::cerr << msg << '\n';
}