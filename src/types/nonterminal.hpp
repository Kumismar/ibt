/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-30 20:24
 */

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

class Nonterminal : public Symbol
{
private:
    const NonterminalType ntType;

public:
    Nonterminal(const NonterminalType t);
    Nonterminal(const Nonterminal& old);

    ~Nonterminal() override
    {
    }

    bool operator==(const NonterminalType& other) const;
    bool operator==(const Nonterminal& other) const;

    NonterminalType GetNonterminalType() const;
    std::string GetTypeString() const override;
    Nonterminal* Clone() const override;
};