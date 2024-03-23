/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-23 17:34
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