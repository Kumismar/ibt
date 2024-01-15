#include "headers/grammar_1.hpp"
#include "headers/stack_item.hpp"
#include <list>

std::list<StackItem> Grammar1::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = this->rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}