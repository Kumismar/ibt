#pragma once

#include "stack_item.hpp"
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

typedef std::list<StackItem*> Rule;
typedef std::list<StackItem*> AnalysisStack;