#pragma once

#include "stack_item.hpp"
#include <list>

typedef std::list<StackItem*> Rule;

class Grammar
{
public:
    virtual ~Grammar()
    {
    }

    virtual Rule Expand(unsigned ruleNumber) = 0;
};
