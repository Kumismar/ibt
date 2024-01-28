#pragma once

#include "grammar.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <list>
#include <vector>

class Grammar4 : public Grammar
{
private:
    const std::vector<std::list<StackItem>> rightSideRules = {
        {}
    };

public:
    ~Grammar4()
    {
    }

    std::list<StackItem> Expand(unsigned ruleNumber) override;
};