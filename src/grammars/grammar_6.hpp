#pragma once

#include "grammar.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <list>
#include <vector>

class Grammar6 : public Grammar
{
private:
    static const std::vector<std::list<StackItem>> rightSideRules;

public:
    ~Grammar6() override
    {
    }

    std::list<StackItem> Expand(unsigned ruleNumber) override;
};