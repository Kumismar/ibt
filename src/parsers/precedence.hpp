#pragma once

#include "parser.hpp"
#include "token.hpp"
#include <list>
#include <stack>

class PrecedenceParser : public Parser
{
private:
    std::stack<StackItem*>& pushdown;

    Token* findFirstTokenInStack();
    void findFirstRule(std::list<StackItem*>& emptyRule);
    bool parseIsSuccessful(Token& inputToken);
    void insertExpressionEnd(std::list<Token>& inputTape) const;

public:
    ~PrecedenceParser() override
    {
    }

    PrecedenceParser(std::stack<StackItem*>& stack)
        : pushdown(stack)
    {
    }
    void Parse(std::list<Token>& inputTape) override;
};
