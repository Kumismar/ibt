/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-05-02 10:34
 */

#include "grammar_6.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"

const std::vector<Rule> Grammar6::rightSideRules = {
    { new Nonterminal(nType) },
    { new Token(tEps) },
    { new Token(tInt) },
    { new Token(tFloat) },
    { new Token(tString) },
    { new Token(tBool) }
};

Rule Grammar6::Expand(unsigned ruleNumber)
{
    Rule toReturn = Grammar6::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

void Grammar6::Cleanup()
{
    for (const Rule& rule: rightSideRules) {
        for (Symbol* member: rule) {
            delete member;
        }
    }
}