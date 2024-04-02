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
"if"            { Token::AddToken(tIf, None); }
"while"         { Token::AddToken(tWhile, None); }
"for"           { Token::AddToken(tFor, None); }
"return"        { Token::AddToken(tReturn, None); }
";"             { Token::AddToken(tSemi, None); }
"elseif"        { Token::AddToken(tElseif, None); }
"else"          { Token::AddToken(tElse, None); }
"("             { Token::AddToken(tLPar, None); }
")"             { Token::AddToken(tRPar, None); }
"{"             { Token::AddToken(tLCurl, None); }
"}"             { Token::AddToken(tRCurl, None); }
"+"             { Token::AddToken(tPlus, None); }
"*"             { Token::AddToken(tMul, None); }
"/"             { Token::AddToken(tDiv, None); }
"=="            { Token::AddToken(tEq, None); }
"!="            { Token::AddToken(tNEq, None); }
"<"             { Token::AddToken(tLess, None); }
"<="            { Token::AddToken(tLEq, None); }
">"             { Token::AddToken(tGreater, None); }
">="            { Token::AddToken(tGEq, None); }
"="             { Token::AddToken(tAssign, None); }
"&&"            { Token::AddToken(tAnd, None); }
"||"            { Token::AddToken(tOr, None); }
"!"             { Token::AddToken(tExcl, None); }
","             { Token::AddToken(tComma, None); }
":"             { Token::AddToken(tColon, None); }
"."             { Token::AddToken(tConcat, None); }
"function"      { Token::AddToken(tFunction, None); }
[0-9]+          { Token::AddToken(tConst, Int); }
[0-9]+"."[0-9]+ { Token::AddToken(tConst, Float); }
"true"|"false"  { Token::AddToken(tConst, Bool); }
"int"           { Token::AddToken(tInt, None); }
"float"         { Token::AddToken(tFloat, None); }
"bool"          { Token::AddToken(tBool, None); }
"string"        { Token::AddToken(tString, None); }
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
        Token::AddToken(tMinus, None); 
    else
        Token::AddToken(tUnMinus, None);
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