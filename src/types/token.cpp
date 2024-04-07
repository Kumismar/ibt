/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-22 22:14
 * @ Modified time: 2024-04-07 22:29
 */

#include "token.hpp"
#include "internal_error.hpp"
#include "lex.yy.h"
#include "stack_item.hpp"
#include <string>

InputTape inputTape;

Token::Token()
{
    this->data.type = None;
    this->symbType = Token_t;
}

Token::Token(const TokenType t)
    : type(t)
{
    if (t == tEnd) {
        this->data.type = String;
        this->data.value.stringVal = new std::string("EOF");
    }
    else {
        this->data.type = None;
    }
    this->symbType = Token_t;
}


Token::Token(const Token& other)
    : type(other.GetTokenType())
{
    this->symbType = Token_t;
    this->lineno = other.GetLineNo();
    if (other.data.type == String) {
        this->data.type = String;
        this->data.value.stringVal = new std::string(*other.data.value.stringVal);
    }
    else {
        this->data = other.data;
    }
}

Token::~Token()
{
    if (this->data.type == String && this->data.value.stringVal != nullptr) {
        delete this->data.value.stringVal;
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
    this->lineno = yyget_lineno();
    std::string tmp = yytext;

    this->data.type = dtype;
    switch (dtype) {
        case Int:
            this->data.value.intVal = std::stoi(tmp);
            break;
        case Float:
            this->data.value.floatVal = std::stof(tmp);
            break;
        case String:
            this->data.value.stringVal = new std::string(tmp);
            break;
        case Bool:
            this->data.value.boolVal = (tmp == "true");
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
            return "EOF";
        case tExpEnd:
            return "EOE";
        case tFuncConst:
            return "funcConst";
        case tFuncEnd:
            return "funcEnd";
        default:
            throw InternalError("Unknown token type in Token::GetTypeString()\n");
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
            return *this->data.value.stringVal;
        case Bool:
            return this->data.value.boolVal ? "true" : "false";
        case None:
            return this->GetTypeString();
        default:
            throw InternalError("Unknown data type in Token::GetDataString()\n");
    }
}

unsigned int Token::GetLineNo() const
{
    return this->lineno;
}

Token* Token::Clone() const
{
    return new Token(*this);
}

DataType Token::GetDataType() const
{
    return this->data.type;
}


void Token::AddToken(TokenType ttype, DataType dtype)
{
    extern TokenType previousToken;
    Token* token = new Token();
    token->SetTokenType(ttype);
    token->SetData(dtype);
    inputTape.push_back(token);
    previousToken = ttype;
}