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

protected:
    bool success = false;

public:
    virtual ~Parser()
    {
    }

    virtual void Parse(std::list<Token>& inputTape) = 0;

    ParserType GetParserType();
    void SetParserType(ParserType type);
};