#pragma once

#include "nonterminal.hpp"
#include "token.hpp"
#include <list>
#include <stack>

class PredictiveParser
{
private:
    std::stack<StackItem> pushdown;
    StackItem stackTop;
    Token inputToken;
    bool success = false;
    bool fail = false;

public:
    void Parse(std::list<Token>& inputTape);
};