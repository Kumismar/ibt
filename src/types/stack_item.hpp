#pragma once

#include <string>

class StackItem
{
public:
    virtual ~StackItem()
    {
    }

    bool operator==(const StackItem& other) const;
    bool operator!=(const StackItem& other) const;

    virtual std::string GetTypeString() const = 0;
    virtual StackItem* Clone() const = 0;
};