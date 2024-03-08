#pragma once

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
    std::list<StackItem*> rightSideRule;
    Logger();
    ~Logger();

    void clearRule();

public:
    static Logger* GetInstance();
    void AddLeftSide(StackItem* leftSide);
    void AddRightSide(std::list<StackItem*>& rightSide);
    void PrintRule();
    void PrintTokens();
    static void Cleanup();
};