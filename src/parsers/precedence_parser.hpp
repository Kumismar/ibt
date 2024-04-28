/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-04-28 21:54
 */

#pragma once

#include "precedence_table.hpp"
#include "predictive_parser.hpp"
#include "token.hpp"


class PrecedenceParser
{
private:
    AnalysisStack& pushdown;
    AnalysisStack analysisPushdown;
    Token* inputToken = nullptr;
    PrecedenceTable* table = nullptr;

    bool parseIsSuccessful();
    void clearStack();
    void cleanUpAfterParsing();
    void initPrecedenceParsing();
    void parseFunction();
    void handleSpecialCases();

public:
    ~PrecedenceParser();
    PrecedenceParser(AnalysisStack& stack);
    void Parse();
};
