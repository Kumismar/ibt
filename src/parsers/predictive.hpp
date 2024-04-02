/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#pragma once

#include "grammar.hpp"
#include "ll_table.hpp"
#include "stack_item.hpp"
#include "token.hpp"

typedef std::list<Symbol*> AnalysisStack;
typedef std::list<Symbol*> Rule;

class PrecedenceParser;

class PredictiveParser
{
private:
    AnalysisStack& pushdown;
    Symbol* stackTop = nullptr;
    Token* inputToken = nullptr;
    LLTable* table = nullptr;
    bool parsingFunction = false;
    bool firstFuncName = false;

    bool returnedEpsilon(Rule& expandedRule);
    void parseNonterminal();
    void parseToken();
    void parseEnd();
    void parseExpression();

public:
    ~PredictiveParser();
    PredictiveParser(AnalysisStack& stack);

    void InitSyntaxAnalysis();
    void Parse(bool parseFunction);
    void ClearStack();
};