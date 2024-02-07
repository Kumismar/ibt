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

    bool operator==(const Expression& other) const;
    bool operator!=(const Expression& other) const;

    ExpressionType GetExpressionType() const;
};