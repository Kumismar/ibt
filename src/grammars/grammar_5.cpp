#include "grammar_5.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<std::list<StackItem*>> Grammar5::rightSideRules = {
    { new Token(tLCurl), new Nonterminal(nStatements), new Token(tRCurl) },
    { new Nonterminal(nStatement) },
    { new Nonterminal(nStatement), new Nonterminal(nStatements) },
    { new Token(tEps) }
};

std::list<StackItem*> Grammar5::Expand(unsigned ruleNumber)
{
    std::list<StackItem*> toReturn = Grammar5::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

void Grammar5::Cleanup()
{
    for (const std::list<StackItem*>& rule: rightSideRules) {
        for (StackItem* member: rule) {
            delete member;
        }
    }
}