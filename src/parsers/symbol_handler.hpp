/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 21:56
 * @ Modified time: 2024-04-28 22:51
 */

#pragma once

#include "predictive_parser.hpp"
#include "table_index.hpp"

class SymbolHandler
{
private:
    AnalysisStack& stack;

    void pushRule(Rule& expandedRule, Nonterminal* stackNT);
    bool returnedEpsilon(Rule& rule);

public:
    SymbolHandler(AnalysisStack& stack);
    void Expand(bool parsingFunction, LLTableIndex tableItem);
    void Pop();
};