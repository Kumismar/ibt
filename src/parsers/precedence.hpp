/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-04-02 23:09
 */

#pragma once

#include "logger.hpp"
#include "precedence_table.hpp"
#include "predictive.hpp"
#include "token.hpp"


class PrecedenceParser
{
private:
    AnalysisStack& pushdown;
    AnalysisStack analysisPushdown;
    Token* inputToken = nullptr;
    PrecedenceTable* table = nullptr;

    Token* findFirstTokenInStack();
    void findFirstRule(Rule& emptyRule);
    bool parseIsSuccessful();
    void insertExpressionEnd();
    void pushPrecedence();
    void clearStack();
    void insertFunctionEnd();
    void reduce();
    void cleanUpAfterParsing();
    void push();
    void initPrecedenceParsing();
    void skipFunctionCall(InputTape::iterator& token);
    void skipOperand(InputTape::iterator& token);
    void skipOperandInParentheses(InputTape::iterator& token);
    bool isOperator(Token& token);
    void parseFunction();

public:
    ~PrecedenceParser();
    PrecedenceParser(AnalysisStack& stack);
    void Parse();
};
