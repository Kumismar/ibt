#pragma once

#include "nonterminal.hpp"
#include "token.hpp"
#include <stack>

class PushdownAutomaton
{
private:
    std::stack<Nonterminal> pushdown;
    Token inputToken;
    Token stackTop;

public:
    void Parse();
};