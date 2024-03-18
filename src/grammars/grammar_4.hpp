/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#pragma once

#include "grammar.hpp"
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