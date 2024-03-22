/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#include "parser.hpp"

int Parser::functionCounter = 0;

ParserType Parser::GetParserType()
{
    return this->parserType;
}