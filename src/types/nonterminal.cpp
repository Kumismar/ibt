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