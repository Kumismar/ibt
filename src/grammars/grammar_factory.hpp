/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#pragma once

#include "grammar.hpp"

class GrammarFactory
{
public:
    static Grammar* CreateGrammar(unsigned grammarNumber);
};