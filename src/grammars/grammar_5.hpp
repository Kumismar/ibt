#pragma once

#include "grammar.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <list>
#include <vector>

class Grammar5 : public Grammar
{
private:
    static const std::vector<Rule> rightSideRules;

public:
    ~Grammar5() override
    {
    }

    Rule Expand(unsigned ruleNumber) override;
    static void Cleanup();
};