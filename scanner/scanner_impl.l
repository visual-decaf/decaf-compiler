%option noyywrap
%option c++

%{
    #undef yyFlexLexer
    #include "scanner.h"
    #include <cstring>
    #include <iostream>
%}

%option yyclass="decaf::Scanner"

DIGIT [0-9]
HEX_DIGIT [0-9a-fA-F]
INTEGER {DIGIT}+
HEX_INTEGER ("0x"|"0X"){HEX_DIGIT}+

%%

{INTEGER} {
    emit({token_type::INTEGER, YYText()});
}
{HEX_INTEGER} {
    emit({token_type::HEX_INTEGER, YYText()});
}

"+" { emit({token_type::PLUS, YYText()}); }
"-" { emit({token_type::MINUS, YYText()}); }
"*" { emit({token_type::STAR, YYText()}); }
"/" { emit({token_type::SLASH, YYText()}); }
"%" { emit({token_type::PERCENT, YYText()}); }
[ \t] {}

"\n" {
    emit({token_type::EOL, YYText()});
    return token_type::EOL;
 }

<<EOF>> {
    emit({token_type::YYEOF});
    return token_type::YYEOF;
}

. {
    emit({token_type::INVALID, YYText()});
    LexerError("Unrecognized token");
}

%%