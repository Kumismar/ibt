#include "nonterminal.hpp"
#include "stack_item.hpp"

Nonterminal::Nonterminal(NonterminalType t)
    : ntType(t)
{
    this->itemType = Nonterminal_t;
}

bool Nonterminal::operator==(const Nonterminal& other) const
{
    return (this->ntType == other.GetNonterminalType());
}

NonterminalType Nonterminal::GetNonterminalType() const
{
    return this->ntType;
}

std::string Nonterminal::GetTypeString() const
{
    switch (this->ntType) {
        case nProgram:
            return "<program>";
        case nStatementList:
            return "<statementList>";
        case nStatement:
            return "<statement>";
        case nIf2:
            return "<if>";
        case nReturnExp:
            return "<returnExp>";
        case nFunctionCall:
            return "<functionCall>";
        case nFunctionDef:
            return "<functionDef>";
        case nParams:
            return "<params>";
        case nParams2:
            return "<params2>";
        case nFuncType:
            return "<funcType>";
        case nExpression:
            return "<expression>";
        case nArgs:
            return "<args>";
        case nArgs2:
            return "<args2>";
        case nCodeBlock:
            return "<codeBlock>";
        case nStatements:
            return "<statements>";
        case nVoluntaryType:
            return "<voluntaryType>";
        case nType:
            return "<type>";
        default:
            return "unknown";
    }
}