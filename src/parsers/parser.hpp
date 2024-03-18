#pragma once

#include "stack_item.hpp"
#include <list>

typedef enum
{
    Predictive,
    Precedence
} ParserType;

class Parser
{
protected:
    static int functionCounter;

public:
    virtual ~Parser()
    {
    }

    virtual void Parse() = 0;

    ParserType GetParserType();
    void SetParserType(ParserType type);
};

typedef std::list<StackItem*> Rule;
typedef std::list<StackItem*> AnalysisStack;