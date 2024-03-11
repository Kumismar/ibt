#pragma once

#include "grammar.hpp"
#include "stack_item.hpp"
#include <list>
#include <vector>

class Grammar4 : public Grammar
{
private:
    static const std::vector<Rule> rightSideRules;

public:
    ~Grammar4() override
    {
    }

    Rule Expand(unsigned ruleNumber) override;
    bool IsRule(Rule& stack);
    static void Cleanup();
};