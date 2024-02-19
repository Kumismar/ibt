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
    std::string GetTypeString() const override;
};