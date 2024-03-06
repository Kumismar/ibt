#pragma once

#include "parser.hpp"
#include "token.hpp"
#include <list>
#include <stack>

class PrecedenceParser : public Parser
{
private:
    std::stack<StackItem*>& pushdown;
    std::stack<StackItem*> analysisPushdown;

    Token* findFirstTokenInStack();
    void findFirstRule(std::list<StackItem*>& emptyRule);
    bool parseIsSuccessful(Token& inputToken);
    void insertExpressionEnd(InputTape& inputTape) const;
    void pushPrecedence();
    void clearStack();

public:
    ~PrecedenceParser() override
    {
    }

    PrecedenceParser(std::stack<StackItem*>& stack)
        : pushdown(stack)
    {
    }
    void Parse(InputTape& inputTape) override;
};
