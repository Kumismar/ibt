#include "nonterminal.hpp"
#include "internal_error.hpp"
#include "stack_item.hpp"

Nonterminal::Nonterminal(const NonterminalType t)
    : ntType(t)
{
    this->itemType = Nonterminal_t;
}

Nonterminal::Nonterminal(const Nonterminal& old)
    : ntType(old.GetNonterminalType())
{
    this->itemType = Nonterminal_t;
}

bool Nonterminal::operator==(const NonterminalType& other) const
{
    return (this->ntType == other);
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
            return "<if2>";
        case nDeclOrExpr:
            return "<declOrExpr>";
        case nReturnExp:
            return "<returnExp>";
        case nFunctionDef:
            return "<functionDef>";
        case nParams:
            return "<params>";
        case nParams2:
            return "<params2>";
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
            throw InternalErrorException("Unknown nonterminal type\n");
    }
}

StackItem* Nonterminal::Clone() const
{
    return new Nonterminal(*this);
}