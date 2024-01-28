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
    tPLus,
    tMinus,
    tMul,
    tDiv,
    tConcat,
    tExcl,
    tAnd,
    tOr,
    tEq,
    tNEq,
    tConst,
    tComma,
    tInt,
    tFloat,
    tString,
    tBool,
    tEps,
    tEnd
} TokenType;

class Token : public StackItem
{
private:
    TokenType type;

public:
    Token(TokenType t)
        : type(t)
    {
    }

    ~Token()
    {
    }

    TokenType GetTokenType() const;

    bool operator==(Token& t)
    {
        return (this->type == t.type);
    }
};