%{
    #include "parser_impl.h"
    #define YY_DECL int yylex(yy::parser::value_type* yylval)
    #include <cstring>
    #include <iostream>
%}

%option noyywrap

DIGIT [0-9]
INTEGER ("+"|"-")?{DIGIT}+

%%

{INTEGER} {
    yylval->emplace<int>(atoi(yytext));
    return yy::parser::token::INTEGER;
}

"+" { return yy::parser::token::PLUS; }
"-" { return yy::parser::token::MINUS; }
"*" { return yy::parser::token::STAR; }
"/" { return yy::parser::token::SLASH; }
[ \t] {}
"\n" { return yy::parser::token::EOL; }
<<EOF>> { return yy::parser::token::YYEOF; }

%%