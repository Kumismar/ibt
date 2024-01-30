#pragma once

#include "expression.hpp"
#include <stack>

class PrecedenceParser
{
private:
    std::stack<Expression> expStack;
    Expression top;
    Expression second;
    Expression third;

public:
    void Parse(std::list<Token>& inputTape);
};
