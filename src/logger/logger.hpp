#pragma once

#include "grammar.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <fstream>
#include <list>

class Logger
{
private:
    static Logger* instance;
    std::ofstream file;
    StackItem* leftSideRule;
    Rule rightSideRule;
    Logger();
    ~Logger();

    void clearRule();

public:
    static Logger* GetInstance();
    void AddLeftSide(StackItem* leftSide);
    void AddRightSide(Rule& rightSide);
    void PrintRule();
    void PrintTokens();
    static void Cleanup();
};