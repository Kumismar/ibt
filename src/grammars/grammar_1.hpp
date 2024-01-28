#pragma once

#include "grammar.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <list>
#include <vector>

class Grammar1 : public Grammar
{
private:
    const std::vector<std::list<StackItem>> rightSideRules = {
        { Nonterminal(nStatement), Nonterminal(nStatementList) },
        { Nonterminal(nFunctionDef), Nonterminal(nStatementList) },
        { Nonterminal(nStatement), Nonterminal(nStatementList) },
        { Nonterminal(nFunctionDef), Nonterminal(nStatementList) },
        { Token(tEps) }
    };

public:
    ~Grammar1()
    {
    }

    std::list<StackItem> Expand(unsigned ruleNumber) override;
};