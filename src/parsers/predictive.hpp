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
    std::list<StackItem*>& pushdown;
    StackItem* stackTop = nullptr;
    Token* inputToken = nullptr;
    LLTable table;

    bool returnedEpsilon(std::list<StackItem*>& expandedRule);

public:
    ~PredictiveParser()
    {
    }

    PredictiveParser(std::list<StackItem*>& stack)
        : pushdown(stack)
    {
    }

    void InitSyntaxAnalysis();
    void Parse(InputTape& inputTape) override;
    void ClearStack();
};