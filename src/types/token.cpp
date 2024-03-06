#include "token.hpp"
#include "internal_error.hpp"
#include "lex.yy.h"
#include <cstring>
#include <iostream>
#include <string>

InputTape inputTape;

Token::Token(TokenType t)
    : type(t)
{
    this->itemType = Token_t;
}

Token::~Token()
{
    if (this->data.type == String) {
        free(this->data.value.stringVal);
    }
}

bool Token::operator==(const Token& other) const
{
    return this->type == other.GetTokenType();
}

bool Token::operator!=(const Token& other) const
{
    return !(*this == other);
}

bool Token::operator==(const TokenType& other) const
{
    return (this->type == other);
}

bool Token::operator!=(const TokenType& other) const
{
    return !(*this == other);
}

TokenType Token::GetTokenType() const
{
    return this->type;
}

void Token::SetTokenType(TokenType t)
{
    this->type = t;
}

void Token::SetData(DataType dtype)
{
    char* tmp = strndup(yytext, yyleng);

    this->data.type = dtype;
    switch (dtype) {
        case Int:
            this->data.value.intVal = std::stoi(tmp);
            break;
        case Float:
            this->data.value.floatVal = std::stof(tmp);
            break;
        case String:
            this->data.value.stringVal = tmp;
            break;
        case Bool:
            this->data.value.boolVal = (std::string(tmp) == "true");
            break;
        case None:
            break;
    }
}

std::string Token::GetTypeString() const
{
    switch (this->type) {
        case tIf:
            return "if";
        case tWhile:
            return "while";
        case tFor:
            return "for";
        case tReturn:
            return "return";
        case tSemi:
            return ";";
        case tElseif:
            return "elseif";
        case tElse:
            return "else";
        case tLPar:
            return "(";
        case tRPar:
            return ")";
        case tFunction:
            return "function";
        case tFuncName:
            return "funcName";
        case tVariable:
            return "variable";
        case tComma:
            return ",";
        case tColon:
            return ":";
        case tPlus:
            return "+";
        case tUnMinus:
            return "un-";
        case tMinus:
            return "-";
        case tMul:
            return "*";
        case tDiv:
            return "/";
        case tConcat:
            return ".";
        case tAnd:
            return "&&";
        case tOr:
            return "||";
        case tEq:
            return "==";
        case tNEq:
            return "!=";
        case tGreater:
            return ">";
        case tLess:
            return "<";
        case tGEq:
            return ">=";
        case tLEq:
            return "<=";
        case tExcl:
            return "!";
        case tAssign:
            return "=";
        case tConst:
            return "constant";
        case tInt:
            return "int";
        case tFloat:
            return "float";
        case tString:
            return "string";
        case tBool:
            return "bool";
        case tLCurl:
            return "{";
        case tRCurl:
            return "}";
        case tEps:
            return "epsilon";
        case tEnd:
            return "end of input";
        case tExpEnd:
            return "end of expression";
        default:
            throw InternalErrorException("Unknown token type in Token::GetTypeString()\n");
    }
}

std::string Token::GetDataString() const
{
    switch (this->data.type) {
        case Int:
            return std::to_string(this->data.value.intVal);
        case Float:
            return std::to_string(this->data.value.floatVal);
        case String:
            return this->data.value.stringVal;
        case Bool:
            return this->data.value.boolVal ? "true" : "false";
        case None:
            return "none";
        default:
            throw InternalErrorException("Unknown data type in Token::GetDataString()\n");
    }
}
