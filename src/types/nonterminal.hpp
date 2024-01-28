#pragma once

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

class Nonterminal : public StackItem
{
private:
    const NonterminalType type;

public:
    Nonterminal(NonterminalType t)
        : type(t)
    {
    }

    ~Nonterminal()
    {
    }

    NonterminalType GetType() const;
};