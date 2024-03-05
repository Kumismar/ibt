%option header-file="lex.yy.h"

%{
#include "token.hpp"
%}

%{
TokenType previous_token = tEps;
void add_token(TokenType ttype, DataType dtype) {
    Token token;
    token.SetTokenType(ttype);
    token.SetData(dtype, yytext);
    inputTape.push_back(token);
    previous_token = ttype;
}
%}

%x COMMENT
%x LINE_COMMENT

%%

[ \n\t]         ;
"if"            { add_token(tIf, None); }
"while"         { add_token(tWhile, None); }
"for"           { add_token(tFor, None); }
"return"        { add_token(tReturn, None); }
";"             { add_token(tSemi, None); }
"elseif"        { add_token(tElseif, None); }
"else"          { add_token(tElse, None); }
"("             { add_token(tLPar, None); }
")"             { add_token(tRPar, None); }
"{"             { add_token(tLCurl, None); }
"}"             { add_token(tRCurl, None); }
"+"             { add_token(tPlus, None); }
"*"             { add_token(tMul, None); }
"/"             { add_token(tDiv, None); }
"=="            { add_token(tEq, None); }
"!="            { add_token(tNEq, None); }
"<"             { add_token(tLess, None); }
"<="            { add_token(tLEq, None); }
">"             { add_token(tGreater, None); }
">="            { add_token(tGEq, None); }
"="             { add_token(tAssign, None); }
"&&"            { add_token(tAnd, None); }
"||"            { add_token(tOr, None); }
"!"             { add_token(tExcl, None); }
","             { add_token(tComma, None); }
":"             { add_token(tColon, None); }
"."             { add_token(tConcat, None); }
"function"      { add_token(tFunction, None); }
[0-9]+          { add_token(tConst, Int); }
[0-9]+"."[0-9]+ { add_token(tConst, Float); }
"true"|"false"  { add_token(tConst, Bool); }
"int"           { add_token(tInt, None); }
"float"         { add_token(tFloat, None); }
"bool"          { add_token(tBool, None); }
"string"        { add_token(tString, None); }
"\"(?:\\[\\nt\"xX]|[^\x20-\xFF\\\"]|\\x[0-9a-fA-F]{2})*\"" { add_token(tConst, String); }
[a-zA-Z_][a-zA-Z0-9_]* { 
    char next_char = yyinput();
    while (next_char == ' ' || next_char == '\n' || next_char == '\t')
        next_char = yyinput();
    unput(next_char);
    if (next_char == '(')
        add_token(tFuncName, String); 
    else
        add_token(tVariable, String); 
}

"-"               { 
    if (previous_token == tVariable || previous_token == tConst || previous_token == tRPar)
        add_token(tMinus, None); 
    else
        add_token(tUnMinus, None);
}

"//" {
    BEGIN(LINE_COMMENT); 
}

"/*" {
    BEGIN(COMMENT); 
}

<COMMENT>"*/" {
    BEGIN(INITIAL); 
}

<COMMENT>. {
}

<LINE_COMMENT>"\n" {
    BEGIN(INITIAL); 
}

<LINE_COMMENT>. {
}

%%

int yywrap()
{
    return 1;
}