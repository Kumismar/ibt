#include "token.hpp"

Token::Token(TokenType t)
    : type(t)
{
    this->itemType = Token_t;
}

bool Token::operator==(const Token& other) const
{
    return (this->type == other.GetTokenType());
}

TokenType Token::GetTokenType() const
{
    return this->type;
}