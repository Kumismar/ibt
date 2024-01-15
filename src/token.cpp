#include "headers/token.hpp"
#include "headers/token_type.hpp"

const TokenType& Token::GetType() const
{
    return this->type;
}