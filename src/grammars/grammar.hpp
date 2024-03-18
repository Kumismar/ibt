/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

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
