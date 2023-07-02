%language "C++"
%define api.value.type variant
/* %define api.token.constructor */
%define parse.error verbose
%define parse.trace

%code {
    int yylex(yy::parser::value_type* yylval);
}

%nterm <int> expr

%token <int> INTEGER
%token PLUS '+' MINUS '-'
%token STAR '*' SLASH '/'
%token EOL

/* Expressions */
%left PLUS MINUS
%left STAR SLASH

%%

input: 
    %empty
    | input expr EOL {
        std::cout << $2 << std::endl;
    }
    ;

expr:
    expr PLUS expr { $$ = $1 + $3; }
    | expr MINUS expr { $$ = $1 - $3; }
    | expr STAR expr { $$ = $1 * $3; }
    | expr SLASH expr { $$ = $1 / $3; }
    | INTEGER
    ;
%%

void yy::parser::error(const std::string& msg) {
    std::cerr << msg << '\n';
}