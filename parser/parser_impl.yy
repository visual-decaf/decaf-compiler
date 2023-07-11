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

%nterm <std::shared_ptr<decaf::ast::Expr>> expression
%nterm <std::shared_ptr<decaf::ast::Expr>> arithmeticBinaryExpr
%nterm <std::shared_ptr<decaf::ast::Expr>> arithmeticUnaryExpr
%nterm <std::shared_ptr<decaf::ast::Expr>> intConstant
%nterm <std::shared_ptr<decaf::ast::Expr>> group
%nterm <std::shared_ptr<decaf::ast::Expr>> logicBinaryExpr
%nterm <std::shared_ptr<decaf::ast::Expr>> boolConstant

%token <int> INTEGER
%token <int> HEX_INTEGER
%token PLUS "+" MINUS "-"
%token STAR "*" SLASH "/" PERCENT "%"
%token LEFT_PAREN "(" RIGHT_PAREN ")"
%token LOGIC_AND "&&" LOGIC_OR "||"
%token EOL
%token INVALID

/* Keywords */
%token TRUE "true" FALSE "false"

/* Expressions */
%left LOGIC_OR
%left LOGIC_AND
%left PLUS MINUS
%left STAR SLASH PERCENT
%left UNARY_MINUS

%%

input: 
    %empty
    | input expression EOL {
        driver.ast_root = $2;
    }
    ;

expression:
    arithmeticBinaryExpr
    | arithmeticUnaryExpr
    | logicBinaryExpr
    | group
    | intConstant
    | boolConstant
    ;

arithmeticBinaryExpr: 
    expression "+" expression {
        $$ = std::make_shared<ArithmeticBinary>(
            $1,
            ArithmeticBinary::Operation::PLUS,
            $3
        );
    }
    | expression "-" expression {
        $$ = std::make_shared<ArithmeticBinary>(
            $1,
            ArithmeticBinary::Operation::MINUS,
            $3
        );
    }
    | expression "*" expression {
        $$ = std::make_shared<ArithmeticBinary>(
            $1,
            ArithmeticBinary::Operation::MULTIPLY,
            $3
        );
    }
    | expression "/" expression {
        $$ = std::make_shared<ArithmeticBinary>(
            $1,
            ArithmeticBinary::Operation::DIVIDE,
            $3
        );
    }
    | expression "%" expression {
        $$ = std::make_shared<ArithmeticBinary>(
            $1,
            ArithmeticBinary::Operation::MOD,
            $3
        );
    }

arithmeticUnaryExpr:
    "-" expression %prec UNARY_MINUS {
        $$ = std::make_shared<ArithmeticUnary>($2);
    }

logicBinaryExpr:
    expression "&&" expression {
        $$ = std::make_shared<LogicBinary>(
            $1,
            LogicBinary::Operation::LOGIC_AND,
            $3
        );
    }
    | expression "||" expression {
        $$ = std::make_shared<LogicBinary>(
            $1,
            LogicBinary::Operation::LOGIC_OR,
            $3
        );
    }

group:
    "(" expression ")" {
        $$ = std::make_shared<Group>(
            $2
        );
    }
    | "(" error ")" {
        $$ = std::make_shared<Group> (
            nullptr
        );
        yyerrok;
    }

intConstant:
    INTEGER {
        $$ = std::make_shared<IntConstant>($1);
    }
    | HEX_INTEGER {
        $$ = std::make_shared<IntConstant>($1);
    }

boolConstant:
    "true" {
        $$ = std::make_shared<BoolConstant>(true);
    }
    | "false" {
        $$ = std::make_shared<BoolConstant>(false);
    }
    ;

%%

void yy::parser::error(const std::string& msg) {
    driver.has_error = true;
    driver.err_messages.push_back(msg);
}
