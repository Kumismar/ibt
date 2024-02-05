#pragma once

typedef enum
{
    ExpNonterminal,
    ExpToken,
    ExpPrecSymbol
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