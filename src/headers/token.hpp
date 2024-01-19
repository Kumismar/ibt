#pragma once

#include "stack_item.hpp"
#include "token_type.hpp"

class Token : public StackItem
{
private:
    TokenType type;

public:
    Token(TokenType t)
        : type(t)
    {
    }

    ~Token()
    {
    }

    TokenType GetTokenType() const;

    bool operator==(Token& t)
    {
        return (this->type == t.type);
    }
};