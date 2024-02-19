#pragma once

#include "stack_item.hpp"

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
    tLCurl,
    tRCurl,
    tFunction,
    tFuncName,
    tColon,
    tVariable,
    tAssign,
    tPlus,
    tMinus,
    tMul,
    tDiv,
    tConcat,
    tExcl,
    tAnd,
    tOr,
    tEq,
    tNEq,
    tGreater,
    tLess,
    tGEq,
    tLEq,
    tConst,
    tComma,
    tInt,
    tFloat,
    tString,
    tBool,
    tEps,
    // Two auxiliary tokens used as stop
    tEnd,
    tExpEnd
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
};