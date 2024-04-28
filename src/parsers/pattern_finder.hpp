/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 16:10
 * @ Modified time: 2024-04-28 16:21
 */

#pragma once

#include "grammar.hpp"
#include "predictive_parser.hpp"
#include "token.hpp"

class PatternFinder
{
public:
    Token* FindFirstTokenInStack(AnalysisStack& stack);
    void FindFirstRule(AnalysisStack& stack, Rule& emptyRule);
};