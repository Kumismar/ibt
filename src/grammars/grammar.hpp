#pragma once

#include "stack_item.hpp"
#include <list>

class Grammar
{
public:
    virtual ~Grammar()
    {
    }

    virtual std::list<StackItem*> Expand(unsigned ruleNumber) = 0;
};