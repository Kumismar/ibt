/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-23 17:34
 */

#pragma once

#include "grammar.hpp"
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