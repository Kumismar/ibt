%option pointer c++

%{
#include <stdio.h>
#include <stdlib.h>
#include "token.hpp"
#include "lex.hpp"
%}

%{
LexicalAnalyzer lex;
TokenType previous_token = tEps;
void add_token(TokenType type) {
    Token token;
    token.SetTokenType(type);
    token.SetData(yytext);
    lex.AddToken(token);
    previous_token = type;
}
%}

%x COMMENT

%%

"if"            { add_token(tIf); }
"while"         { add_token(tWhile); }
"for"           { add_token(tFor); }
"return"        { add_token(tReturn); }
";"             { add_token(tSemi); }
"elseif"        { add_token(tElseif); }
"else"          { add_token(tElse); }
"("             { add_token(tLPar); }
")"             { add_token(tRPar); }
"function"      { add_token(tFunction); }
[0-9]+          { add_token(tConst); }
[0-9]+"."[0-9]+ { add_token(tFloat); }
[0-9]+"."[0-9]* { add_token(tFloat); }
"true"|"false"  { add_token(tBool); }
"[-]?[0-9]+"    { add_token(tInt); }
"[-]?[0-9]+"."[-]?[0-9]+" { add_token(tFloat); }
"[-]?[0-9]+"."[-]?[0-9]*" { add_token(tFloat); }
[a-zA-Z_][a-zA-Z0-9_]* { 
    int next_char = yyinput();
    unput(next_char);
    if (next_char == '(')
        add_token(tFuncName); 
    else
        add_token(tVariable); 
}

"-"               { 
    if (previous_token == tVariable || previous_token == tConst || previous_token == tRPar)
        add_token(tMinus); 
    else
        add_token(tUnMinus);
}

<INITIAL>"/*" {
    BEGIN(COMMENT); 
}

<COMMENT>"*/" {
    BEGIN(INITIAL); 
}

<COMMENT>. {
}

%%

int yywrap()
{
    return 1;
}