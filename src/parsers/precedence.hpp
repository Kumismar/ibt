/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#pragma once

#include "logger.hpp"
#include "parser.hpp"
#include "precedence_table.hpp"
#include "token.hpp"
#include <stack>

typedef std::list<Token*> FunctionContext;

class PrecedenceParser : public Parser
{
private:
    AnalysisStack& pushdown;
    AnalysisStack analysisPushdown;
    Logger* logger = nullptr;
    PrecedenceTable* table;
    Token* inputToken = nullptr;
    std::stack<FunctionContext> functionContexts;

    Token* findFirstTokenInStack();
    void findFirstRule(Rule& emptyRule);
    bool parseIsSuccessful();
    void insertExpressionEnd() const;
    void pushPrecedence();
    void clearStack();
    void insertFunctionEnd();
    void reduce();
    void initPrecedenceParsing();
    void cleanUpAfterParsing();
    void push();
    void saveFunctionContext();

public:
    ~PrecedenceParser() override
    {
        delete this->table;
    }

    PrecedenceParser(AnalysisStack& stack)
        : pushdown(stack)
    {
        this->table = new PrecedenceTable();
    }
    void Parse() override;
};
