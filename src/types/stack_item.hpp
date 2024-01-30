#pragma once

typedef enum
{
    Token_t,
    Nonterminal_t
} ItemType;

class StackItem
{
private:
    ItemType itemType;

public:
    virtual ~StackItem()
    {
    }

    ItemType GetItemType() const;
};