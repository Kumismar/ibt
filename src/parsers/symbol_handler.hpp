/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 21:56
 * @ Modified time: 2024-04-30 15:06
 */

#pragma once

#include "predictive_parser.hpp"
#include "table_index.hpp"

class SymbolHandler
{
private:
    AnalysisStack& stack;
    Rule rule;

    void pushRule(Nonterminal* stackNT);
    bool returnedEpsilon();

public:
    SymbolHandler(AnalysisStack& stack);
    void Expand(bool parsingFunction, LLTableIndex& tableItem);
    void Pop();
};