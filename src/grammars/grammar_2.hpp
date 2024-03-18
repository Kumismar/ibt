/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#pragma once

#include "grammar.hpp"
#include <vector>

class Grammar2 : public Grammar
{
private:
    static const std::vector<Rule> rightSideRules;

public:
    ~Grammar2() override
    {
    }

    Rule Expand(unsigned ruleNumber) override;

    static void Cleanup();
};