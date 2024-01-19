#pragma once

#include "grammar.hpp"

class GrammarFactory
{
public:
    static Grammar* CreateGrammar(unsigned grammarNumber);
};