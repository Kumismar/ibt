#include "token.hpp"

bool Token::operator==(const Token& other) const
{
    return (this->type == other.GetTokenType());
}

TokenType Token::GetTokenType() const
{
    return this->type;
}