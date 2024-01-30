#pragma once

#include "expression.hpp"
#include "stack_item.hpp"

typedef enum nonterminalType
{
    nProgram,
    nStatementList,
    nStatement,
    nIf2,
    nReturnExp,
    nFunctionDef,
    nParams,
    nParams2,
    nFuncType,
    nExpression,
    nArgs,
    nArgs2,
    nCodeBlock,
    nStatements,
    nType,
} NonterminalType;

class Nonterminal : public StackItem, public Expression
{
private:
    const NonterminalType ntType;

public:
    Nonterminal(NonterminalType t)
        : ntType(t)
    {
    }

    ~Nonterminal() override
    {
    }

    NonterminalType GetNonterminalType() const;
};