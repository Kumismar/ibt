#pragma once

#include "parser.hpp"
#include "token.hpp"
#include <list>
#include <stack>

class PrecedenceParser : public Parser
{
private:
    AnalysisStack& pushdown;
    AnalysisStack analysisPushdown;

    Token* findFirstTokenInStack();
    void findFirstRule(Rule& emptyRule);
    bool parseIsSuccessful(Token& inputToken);
    void insertExpressionEnd(InputTape& inputTape) const;
    void pushPrecedence();
    void clearStack();

public:
    ~PrecedenceParser() override
    {
    }

    PrecedenceParser(AnalysisStack& stack)
        : pushdown(stack)
    {
    }
    void Parse(InputTape& inputTape) override;
};
