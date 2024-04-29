/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-04-29 09:31
 */

#pragma once

#include "grammar.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <fstream>

class Logger
{
private:
    std::string red = "\033[1;31m";
    std::string reset = "\033[0m";

    static Logger* instance;
    std::list<Token*> recentTokens;
    std::ofstream file;
    Symbol* leftSideRule = nullptr;
    Rule rightSideRule;
    bool enableDebugPrint = false;
    bool turnedOff = false;
    Logger();
    ~Logger();

    void clearRule();

public:
    static Logger* GetInstance();
    static void Cleanup();

    void AddLeftSide(Symbol* leftSide);
    void AddRightSide(Rule& rightSide);
    void PrintRule();
    void PrintTokens() const;
    void AddTokenToRecents(Token& token);
    void PrintSyntaxError(const char* message);
    void PrintLexicalError(const char* message);
    void PrintUsageError(const char* message);
    void EnableDebugPrint();
    void TurnOff();
};