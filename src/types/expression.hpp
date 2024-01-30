#pragma once

typedef enum
{
    ExpNonterminal_t,
    ExpToken_t,
    ExpPrecSymbol_t
} ExpressionType;

class Expression
{
private:
    ExpressionType expType;

public:
    virtual ~Expression()
    {
    }

    ExpressionType GetExpressionType() const;
};