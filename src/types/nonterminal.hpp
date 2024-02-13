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
    nFunctionCall,
    nFunctionDef,
    nParams,
    nParams2,
    nFuncType,
    nExpression,
    nArgs,
    nArgs2,
    nCodeBlock,
    nStatements,
    nVoluntaryType,
    nType,
} NonterminalType;

class Nonterminal : public StackItem, public Expression
{
private:
    const NonterminalType ntType;

public:
    Nonterminal(NonterminalType t);

    ~Nonterminal() override
    {
    }

    bool operator==(const Nonterminal& other) const;

    NonterminalType GetNonterminalType() const;
};