#pragma once

typedef enum
{
    Token_t,
    Nonterminal_t
} ItemType;

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