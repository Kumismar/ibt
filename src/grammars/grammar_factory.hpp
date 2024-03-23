/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-23 17:35
 */

#pragma once

#include "grammar.hpp"

class GrammarFactory
{
public:
    static Grammar* CreateGrammar(unsigned grammarNumber);
};