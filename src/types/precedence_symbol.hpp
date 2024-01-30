#pragma once

#include "expression.hpp"

typedef enum
{
    Push, // <
    Reduce, // >
    Equal, // =
    Invalid
} PrecedenceType;

class PrecedenceSymbol : public Expression
{
private:
    PrecedenceType precType;

public:
    PrecedenceSymbol(char prec);

    ~PrecedenceSymbol() override
    {
    }

    PrecedenceType GetPrecedenceType() const;
};