/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#pragma once

#include "ll_table.hpp"
#include "parser.hpp"
#include "stack_item.hpp"
#include "token.hpp"

class PredictiveParser : public Parser
{
private:
    AnalysisStack& pushdown;
    StackItem* stackTop = nullptr;
    Token* inputToken = nullptr;
    LLTable* table;

    bool returnedEpsilon(Rule& expandedRule);
    void parseNonterminal();
    void parseToken();
    void parseEnd();

public:
    ~PredictiveParser();
    PredictiveParser(AnalysisStack& stack);

    void InitSyntaxAnalysis();
    void Parse() override;
    void ClearStack();
};