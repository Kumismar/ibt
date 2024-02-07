#include "grammar_5.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<std::list<StackItem>> Grammar5::rightSideRules = {
    { Token(tLCurl), Nonterminal(nStatements), Token(tRCurl) },
    { Nonterminal(nStatement) },
    { Nonterminal(nStatement), Nonterminal(nStatements) },
    { Token(tEps) },
};

std::list<StackItem> Grammar5::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = Grammar5::rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}