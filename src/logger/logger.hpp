#pragma once

#include "nonterminal.hpp"
#include "stack_item.hpp"
#include <fstream>
#include <list>

class Logger
{
private:
    static Logger* instance;
    std::ofstream file;
    Nonterminal* leftSideRule;
    std::list<StackItem*> rightSideRule;
    Logger();

public:
    static Logger* GetInstance();
    void AddLeftSide(StackItem* leftSide);
    void AddRightSide(std::list<StackItem*>& rightSide);
    void PrintRule();
    void Cleanup();
};