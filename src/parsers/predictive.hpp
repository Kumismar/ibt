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
    std::stack<StackItem*>& pushdown;
    StackItem* stackTop = nullptr;
    Token inputToken = Token(tEnd);

    LLTable table;

    bool returnedEpsilon(std::list<StackItem*>& expandedRule);

public:
    ~PredictiveParser() override
    {
    }

    PredictiveParser(std::stack<StackItem*>& stack)
        : pushdown(stack)
    {
    }

    void InitSyntaxAnalysis();
    void Parse(std::list<Token>& inputTape) override;
};