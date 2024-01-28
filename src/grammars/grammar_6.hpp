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
    const std::vector<std::list<StackItem>> rightSideRules = {
        { Token(tInt) },
        { Token(tFloat) },
        { Token(tString) },
        { Token(tBool) }
    };

public:
    ~Grammar6()
    {
    }

    std::list<StackItem> Expand(unsigned ruleNumber) override;
};