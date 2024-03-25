/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-23 17:35
 */

#pragma once

#include "stack_item.hpp"
#include <list>

typedef std::list<Symbol*> Rule;

class Grammar
{
public:
    virtual ~Grammar()
    {
    }

    virtual Rule Expand(unsigned ruleNumber) = 0;
};
