#pragma once

#include "expression.hpp"
#include "token.hpp"
#include <list>
#include <stack>

class PrecedenceParser
{
private:
    std::stack<Expression> expStack;
    Expression top;
    Expression second;
    Expression third;
    bool success = false;
    bool fail = false;

    Token& findFirstTokenInStack();
    void findFirstRule(std::list<Expression>& emptyRule);

public:
    void Parse(std::list<Token>& inputTape);
};
