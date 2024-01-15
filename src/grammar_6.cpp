#include "headers/grammar_6.hpp"
#include "headers/stack_item.hpp"
#include <list>

std::list<StackItem> Grammar6::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = this->rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}