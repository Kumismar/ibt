#include "grammar_5.hpp"
#include "stack_item.hpp"
#include <list>

std::list<StackItem> Grammar5::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = this->rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}