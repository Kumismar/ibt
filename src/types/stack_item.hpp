#pragma once

#include <string>
typedef enum
{
    Nonterminal_t,
    Token_t,
    PrecSymbol_t
} ItemType;

class StackItem
{
protected:
    ItemType itemType;

public:
    virtual ~StackItem()
    {
    }

    bool operator==(const StackItem& other) const;
    bool operator!=(const StackItem& other) const;

    ItemType GetItemType() const;
    virtual std::string GetTypeString() const = 0;
};