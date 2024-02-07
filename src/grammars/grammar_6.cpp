#include "grammar_6.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<std::list<StackItem>> Grammar6::rightSideRules = {
    { Nonterminal(nType) },
    { Token(tEps) },
    { Token(tInt) },
    { Token(tFloat) },
    { Token(tString) },
    { Token(tBool) }
};


std::list<StackItem> Grammar6::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = Grammar6::rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}