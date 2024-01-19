#pragma once

#include "item_type.hpp"

class StackItem
{
private:
    ItemType type;

public:
    virtual ~StackItem()
    {
    }

    ItemType GetType();
};