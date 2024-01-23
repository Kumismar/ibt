#pragma once

#include "nonterminal_type.hpp"
#include "stack_item.hpp"

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