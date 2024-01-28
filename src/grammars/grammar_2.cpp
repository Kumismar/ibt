#include "grammar_2.hpp"
#include "stack_item.hpp"
#include <list>

std::list<StackItem> Grammar2::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = this->rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}