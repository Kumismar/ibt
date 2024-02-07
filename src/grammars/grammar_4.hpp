#pragma once

#include "grammar.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <list>
#include <stack>
#include <vector>

class Grammar4 : public Grammar
{
private:
    static const std::vector<std::list<Expression>> rightSideRules;

public:
    ~Grammar4() override
    {
    }

    std::list<StackItem> Expand(unsigned ruleNumber) override;
    bool IsRule(std::list<Expression>& stack);
};