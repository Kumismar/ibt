#include "grammar_6.hpp"
#include "stack_item.hpp"
#include <list>

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
        for (StackItem* member: rule) {
            delete member;
        }
    }
}