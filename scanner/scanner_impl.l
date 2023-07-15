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
EXPONENT ("e"|"E")("+"|"-")?{DIGIT}+
NORMAL_FLOAT {DIGIT}+"."{DIGIT}*
FLOAT {NORMAL_FLOAT}{EXPONENT}?

LETTER [a-zA-Z]
IDENTIFIER {LETTER}[a-zA-Z0-9_]

%%

{INTEGER} {
    emit({token_type::INTEGER, YYText()});
}
{HEX_INTEGER} {
    emit({token_type::HEX_INTEGER, YYText()});
}
{FLOAT} {
    emit({token_type::FLOAT, YYText()});
}

"+" { emit({token_type::PLUS, YYText()}); }
"-" { emit({token_type::MINUS, YYText()}); }
"*" { emit({token_type::STAR, YYText()}); }
"/" { emit({token_type::SLASH, YYText()}); }
"%" { emit({token_type::PERCENT, YYText()}); }
"(" { emit({token_type::LEFT_PAREN, YYText()}); }
")" { emit({token_type::RIGHT_PAREN, YYText()}); }
"&&" { emit({token_type::LOGIC_AND, YYText()}); }
"||" { emit({token_type::LOGIC_OR, YYText()});}
"!" { emit({token_type::LOGIC_NOT, YYText()}); }
"<" { emit({token_type::LESS, YYText()}); }
"<=" { emit({token_type::LESS_EQUAL, YYText()}); }
">" { emit({token_type::GREATER, YYText()}); }
">=" { emit({token_type::GREATER_EQUAL, YYText()}); }
"==" { emit({token_type::EQUAL, YYText()}); }
"!=" { emit({token_type::NOT_EQUAL, YYText()}); }
";" { emit({token_type::SEMICOLON, YYText()}); }
"," { emit({token_type::COMMA, YYText()}); }

"true" { emit({token_type::TRUE, YYText()}); }
"false" { emit({token_type::FALSE, YYText()}); }
"Print" { emit({token_type::PRINT, YYText()}); }
"int" { emit({token_type::INT, YYText()}); }
"double" { emit({token_type::DOUBLE, YYText()}); }
"bool" { emit({token_type::BOOL, YYText()}); }

{IDENTIFIER} { emit({token_type::IDENTIFIER, YYText()}); }

[ \t] {}

"\n" {
    // emit({token_type::EOL, YYText()});
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