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

    void parseNonterminal();
    void parseToken();
    void parseEnd();
    void parseExpression(Nonterminal* nt);
    void handleSpecialCases();
    void parseTerminal(Token& t);

public:
    ~PredictiveParser();
    PredictiveParser(AnalysisStack& stack);

    void InitSyntaxAnalysis();
    void Parse(bool parseFunction);
    void ClearStack();
};