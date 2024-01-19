#include "nonterminal.hpp"
#include "nonterminal_type.hpp"

const NonterminalType& Nonterminal::GetType() const
{
    return this->type;
}