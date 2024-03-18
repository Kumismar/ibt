/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#pragma once

#include "grammar.hpp"
#include "stack_item.hpp"
#include <fstream>

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