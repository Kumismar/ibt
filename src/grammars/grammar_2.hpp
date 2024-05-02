/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-05-02 10:20
 */

#pragma once

#include "grammar.hpp"
#include <vector>


/**
 * @brief Second component of Koubp CD grammar system.
 */
class Grammar2 : public Grammar
{
private:
    /**
     * @brief A list of right sides of rules that can be used to expand left sides of rules.
     */
    static const std::vector<Rule> rightSideRules;

public:
    /**
     * @brief A virtual destructor for Grammar2 overriding Grammar destructor.
     */
    ~Grammar2() override;

    /**
     * @brief Expands left side of the rule to right side of the rule.
     * 
     * @param ruleNumber Index of rule to be expanded.
     * @return Sequence of symbols that are right side of the rule.
     */
    Rule Expand(unsigned ruleNumber) override;

    /**
     * @brief Cleans up all the memory allocated by the grammar.
     */
    static void Cleanup();
};