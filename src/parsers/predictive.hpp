#pragma once

#include "ll_table.hpp"
#include "parser.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <list>
#include <stack>

class PredictiveParser : public Parser
{
private:
    AnalysisStack& pushdown;
    StackItem* stackTop = nullptr;
    Token* inputToken = nullptr;
    LLTable table;

    bool returnedEpsilon(Rule& expandedRule);

public:
    ~PredictiveParser()
    {
    }

    PredictiveParser(AnalysisStack& stack)
        : pushdown(stack)
    {
    }

    void InitSyntaxAnalysis();
    void Parse(InputTape& inputTape) override;
    void ClearStack();
};