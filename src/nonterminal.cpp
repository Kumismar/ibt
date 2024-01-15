#include "headers/nonterminal.hpp"
#include "headers/nonterminal_type.hpp"

const NonterminalType& Nonterminal::GetType() const
{
    return this->type;
}