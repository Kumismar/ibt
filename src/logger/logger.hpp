/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-30 21:00
 */

#pragma once

#include "grammar.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <fstream>

class Logger
{
private:
    static Logger* instance;
    std::list<Token*> recentTokens;
    std::ofstream file;
    Symbol* leftSideRule;
    Rule rightSideRule;
    Logger();
    ~Logger();

    void clearRule();

public:
    static Logger* GetInstance();
    static void Cleanup();

    void AddLeftSide(Symbol* leftSide);
    void AddRightSide(Rule& rightSide);
    void PrintRule();
    void PrintTokens();
    void AddTokenToRecents(Token& token);
    void PrintSyntaxError(const char* message);
};