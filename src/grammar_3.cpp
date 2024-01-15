#include "headers/grammar_3.hpp"
#include "headers/stack_item.hpp"
#include <list>

std::list<StackItem> Grammar3::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = this->rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}