#pragma once

#include "token.hpp"
#include <list>

typedef enum
{
    Predictive,
    Precedence
} ParserType;

class Parser
{
private:
    ParserType parserType;

public:
    virtual ~Parser()
    {
    }

    virtual void Parse(InputTape& inputTape) = 0;

    ParserType GetParserType();
    void SetParserType(ParserType type);
};