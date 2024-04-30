/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 16:10
 * @ Modified time: 2024-04-30 13:54
 */

#pragma once

#include "grammar.hpp"
#include "predictive_parser.hpp"
#include "token.hpp"

class PatternFinder
{
private:
    AnalysisStack& stack;

public:
    PatternFinder(AnalysisStack& stack);
    Token* FindFirstToken();
    void FindFirstRule(Rule& emptyRule);
};