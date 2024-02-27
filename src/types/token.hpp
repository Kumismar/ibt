#pragma once

#include "stack_item.hpp"
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
    // Two auxiliary tokens used as stop
    tEnd,
    tExpEnd,
    tEps
} TokenType;

class Token : public StackItem
{
private:
    TokenType type;

public:
    Token(TokenType t);

    ~Token() override
    {
    }

    bool operator==(const Token& other) const;

    TokenType GetTokenType() const;
    std::string GetTypeString() const override;
};