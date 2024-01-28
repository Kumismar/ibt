#include "grammar_6.hpp"
#include "stack_item.hpp"
#include <list>

std::list<StackItem> Grammar6::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = this->rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}