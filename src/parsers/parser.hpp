/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

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
private:
    ParserType parserType;

protected:
    static int functionCounter;

public:
    virtual ~Parser()
    {
    }

    virtual void Parse() = 0;

    ParserType GetParserType();
};

typedef std::list<StackItem*> Rule;
typedef std::list<StackItem*> AnalysisStack;