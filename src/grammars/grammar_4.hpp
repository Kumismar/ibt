#pragma once

#include "expression.hpp"
#include "grammar.hpp"
#include "stack_item.hpp"
#include <list>
#include <vector>

class Grammar4 : public Grammar
{
private:
    static const std::vector<std::list<Expression*>> rightSideRules;

public:
    ~Grammar4() override
    {
    }

    std::list<StackItem*> Expand(unsigned ruleNumber) override;
    bool IsRule(std::list<Expression*>& stack);
    static void Cleanup();
};