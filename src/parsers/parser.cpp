#include "parser.hpp"

int Parser::functionCounter = 0;

ParserType Parser::GetParserType()
{
    return this->parserType;
}

void Parser::SetParserType(ParserType type)
{
    this->parserType = type;
}