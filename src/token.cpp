#include "token.hpp"
#include "token_type.hpp"

TokenType Token::GetTokenType() const
{
    return this->type;
}