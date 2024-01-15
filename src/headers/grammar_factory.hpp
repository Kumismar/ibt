#pragma once

#include "grammar.hpp"

class GrammarFactory
{
public:
    Grammar* CreateGrammar(unsigned grammarNumber) const;
};