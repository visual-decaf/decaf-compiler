%option noyywrap
%option c++

%{
    #undef yyFlexLexer
    #include "scanner.h"
    #include <cstring>
    #include <iostream>
%}

%option yyclass="decaf::scanner"

DIGIT [0-9]
INTEGER ("+"|"-")?{DIGIT}+

%%

{INTEGER} {
    emit({token_type::INTEGER, YYText()});
}

"+" { emit({token_type::PLUS, YYText()}); }
"-" { emit({token_type::MINUS, YYText()}); }
"*" { emit({token_type::STAR, YYText()}); }
"/" { emit({token_type::SLASH, YYText()}); }
[ \t] {}
"\n" { emit({token_type::EOL, YYText()}); }
<<EOF>> {
    emit({token_type::YYEOF, YYText()});
    return token_type::YYEOF;
}

%%