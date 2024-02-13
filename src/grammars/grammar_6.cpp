#include "grammar_6.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<std::list<StackItem*>> Grammar6::rightSideRules = {
    { new Nonterminal(nType) },
    { new Token(tEps) },
    { new Token(tInt) },
    { new Token(tFloat) },
    { new Token(tString) },
    { new Token(tBool) }
};


std::list<StackItem*> Grammar6::Expand(unsigned ruleNumber)
{
    std::list<StackItem*> toReturn = Grammar6::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

void Grammar6::Cleanup()
{
    for (const std::list<StackItem*>& rule: rightSideRules) {
        for (StackItem* member: rule) {
            delete member;
        }
    }
}