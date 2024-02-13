#include "parser.hpp"

ParserType Parser::GetParserType()
{
    return this->parserType;
}

void Parser::SetParserType(ParserType type)
{
    this->parserType = type;
}