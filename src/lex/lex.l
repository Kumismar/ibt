    /*
    *  Author: Ondřej Koumar
    *  Date: 2024-03-18
    */

%option header-file="lex.yy.h" pointer

%{
#include "token.hpp"
#include "lexical_error.hpp"
%}

%{
    TokenType previousToken = tEps;
%}

%x COMMENT
%x LINE_COMMENT
%x STRING

%%

\n              { yylineno++; }
[ \t]           { /* ignore whitespace */ }
"if"            { Token::AddToken(tIf, String); }
"while"         { Token::AddToken(tWhile, String); }
"for"           { Token::AddToken(tFor, String); }
"return"        { Token::AddToken(tReturn, String); }
";"             { Token::AddToken(tSemi, String); }
"elseif"        { Token::AddToken(tElseif, String); }
"else"          { Token::AddToken(tElse, String); }
"("             { Token::AddToken(tLPar, String); }
")"             { Token::AddToken(tRPar, String); }
"{"             { Token::AddToken(tLCurl, String); }
"}"             { Token::AddToken(tRCurl, String); }
"+"             { Token::AddToken(tPlus, String); }
"*"             { Token::AddToken(tMul, String); }
"/"             { Token::AddToken(tDiv, String); }
"=="            { Token::AddToken(tEq, String); }
"!="            { Token::AddToken(tNEq, String); }
"<"             { Token::AddToken(tLess, String); }
"<="            { Token::AddToken(tLEq, String); }
">"             { Token::AddToken(tGreater, String); }
">="            { Token::AddToken(tGEq, String); }
"="             { Token::AddToken(tAssign, String); }
"&&"            { Token::AddToken(tAnd, String); }
"||"            { Token::AddToken(tOr, String); }
"!"             { Token::AddToken(tExcl, String); }
","             { Token::AddToken(tComma, String); }
":"             { Token::AddToken(tColon, String); }
"."             { Token::AddToken(tConcat, String); }
"function"      { Token::AddToken(tFunction, String); }
[0-9]+          { Token::AddToken(tConst, Int); }
[0-9]+"."[0-9]+ { Token::AddToken(tConst, Float); }
"true"|"false"  { Token::AddToken(tConst, Bool); }
"int"           { Token::AddToken(tInt, String); }
"float"         { Token::AddToken(tFloat, String); }
"bool"          { Token::AddToken(tBool, String); }
"string"        { Token::AddToken(tString, String); }
\"(\\.|[^\\"])*\" { Token::AddToken(tConst, String); }

[a-zA-Z_][a-zA-Z0-9_]* { 
    int next_char = yyinput();
    while (next_char == ' ' || next_char == '\n' || next_char == '\t')
        next_char = yyinput();

    if (next_char == '(')
        Token::AddToken(tFuncName, String); 
    else
        Token::AddToken(tVariable, String); 
    unput(next_char);
}

"-" { 
    if (previousToken == tVariable || previousToken == tConst || previousToken == tRPar)
        Token::AddToken(tMinus, String); 
    else
        Token::AddToken(tUnMinus, String);
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

<COMMENT>\n {
    yylineno++;
}

<COMMENT>. {
}

<LINE_COMMENT>"\n" {
    yylineno++;
    BEGIN(INITIAL); 
}

<LINE_COMMENT>. {
}

. { throw LexicalError("Unknown lexeme: " + std::string(yytext) + std::string("on line ") + std::to_string(yylineno) + "\n"); }

%%

int yywrap()
{
    return 1;
}