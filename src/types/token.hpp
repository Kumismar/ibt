/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-22 22:14
 * @ Modified time: 2024-03-30 20:24
 */

#pragma once

#include "stack_item.hpp"
#include <list>
#include <string>

typedef enum tokenType
{
    tIf,
    tWhile,
    tFor,
    tReturn,
    tSemi,
    tElseif,
    tElse,
    tLPar,
    tRPar,
    tFunction,
    tFuncName,
    tVariable,
    tComma,
    tColon,
    tPlus,
    tUnMinus,
    tMinus,
    tMul,
    tDiv,
    tConcat,
    tAnd,
    tOr,
    tEq,
    tNEq,
    tGreater,
    tLess,
    tGEq,
    tLEq,
    tExcl,
    tAssign,
    tConst,
    tInt,
    tFloat,
    tString,
    tBool,
    tLCurl,
    tRCurl,
    // Three auxiliary tokens used as stop
    tEnd,
    tExpEnd,
    tFuncEnd,
    tFuncConst,
    tEps
} TokenType;

typedef enum
{
    Int,
    Float,
    String,
    Bool,
    None
} DataType;

typedef union value
{
    int intVal;
    float floatVal;
    std::string* stringVal = nullptr;
    bool boolVal;
} Value;

typedef struct data {
    DataType type;
    Value value;
} TokenData;

class Token : public Symbol
{
private:
    TokenType type;
    TokenData data;

public:
    Token();
    Token(const Token& old);
    Token(const TokenType type);
    ~Token() override;

    bool operator==(const Token& other) const;
    bool operator!=(const Token& other) const;
    bool operator==(const TokenType& other) const;
    bool operator!=(const TokenType& other) const;

    TokenType GetTokenType() const;
    void SetTokenType(TokenType type);
    void SetData(DataType dtype);
    std::string GetTypeString() const override;
    std::string GetDataString() const;
    Token* Clone() const override;
    static void AddToken(TokenType ttype, DataType dtype);
};

typedef std::list<Token*> InputTape;

extern InputTape inputTape;