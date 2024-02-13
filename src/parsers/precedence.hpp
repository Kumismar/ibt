#pragma once

#include "expression.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <list>
#include <stack>

class PrecedenceParser : public Parser
{
private:
    std::stack<Expression*>& pushdown;

    Token* findFirstTokenInStack();
    void findFirstRule(std::list<Expression*>& emptyRule);
    bool parseIsSuccessful(Token& inputToken);

public:
    ~PrecedenceParser() override
    {
    }

    PrecedenceParser(std::stack<Expression*>& stack)
        : pushdown(stack)
    {
    }
    void Parse(std::list<Token>& inputTape) override;
};
