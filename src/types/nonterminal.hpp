#pragma once

#include "stack_item.hpp"

typedef enum nonterminalType
{
    nProgram,
    nStatementList,
    nStatement,
    nIf2,
    nDeclOrExpr,
    nReturnExp,
    nFunctionCall,
    nFunctionDef,
    nParams,
    nParams2,
    nExpression,
    nArgs,
    nArgs2,
    nCodeBlock,
    nStatements,
    nVoluntaryType,
    nType,
} NonterminalType;

class Nonterminal : public StackItem
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
    std::string GetTypeString() const override;
};