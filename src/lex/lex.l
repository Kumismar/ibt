%option header-file="lex.yy.h" pointer

%{
#include "token.hpp"
%}

%{
TokenType previous_token = tEps;
void add_token(TokenType ttype, DataType dtype) {
    Token token;
    token.SetTokenType(ttype);
    token.SetData(dtype);
    printf("Token: %s\n", token.GetDataString().c_str());
    inputTape.push_back(token);
    previous_token = ttype;
}
%}

%x COMMENT
%x LINE_COMMENT

%%

[ \n\t]         ;
"if"            { add_token(tIf, String); }
"while"         { add_token(tWhile, String); }
"for"           { add_token(tFor, String); }
"return"        { add_token(tReturn, String); }
";"             { add_token(tSemi, String); }
"elseif"        { add_token(tElseif, String); }
"else"          { add_token(tElse, String); }
"("             { add_token(tLPar, String); }
")"             { add_token(tRPar, String); }
"{"             { add_token(tLCurl, String); }
"}"             { add_token(tRCurl, String); }
"+"             { add_token(tPlus, String); }
"*"             { add_token(tMul, String); }
"/"             { add_token(tDiv, String); }
"=="            { add_token(tEq, String); }
"!="            { add_token(tNEq, String); }
"<"             { add_token(tLess, String); }
"<="            { add_token(tLEq, String); }
">"             { add_token(tGreater, String); }
">="            { add_token(tGEq, String); }
"="             { add_token(tAssign, String); }
"&&"            { add_token(tAnd, String); }
"||"            { add_token(tOr, String); }
"!"             { add_token(tExcl, String); }
","             { add_token(tComma, String); }
":"             { add_token(tColon, String); }
"."             { add_token(tConcat, String); }
"function"      { add_token(tFunction, String); }
[0-9]+          { add_token(tConst, Int); }
[0-9]+"."[0-9]+ { add_token(tConst, Float); }
"true"|"false"  { add_token(tConst, Bool); }
"int"           { add_token(tInt, String); }
"float"         { add_token(tFloat, String); }
"bool"          { add_token(tBool, String); }
"string"        { add_token(tString, String); }
"\"(?:\\[\\nt\"xX]|[^\x20-\xFF\\\"]|\\x[0-9a-fA-F]{2})*\"" { add_token(tConst, String); }
[a-zA-Z_][a-zA-Z0-9_]* { 
  

    int next_char = yyinput();
    while (next_char == ' ' || next_char == '\n' || next_char == '\t')
        next_char = yyinput();

    if (next_char == '(')
        add_token(tFuncName, String); 
    else
        add_token(tVariable, String); 
    unput(next_char);
}

"-"               { 
    if (previous_token == tVariable || previous_token == tConst || previous_token == tRPar)
        add_token(tMinus, String); 
    else
        add_token(tUnMinus, String);
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