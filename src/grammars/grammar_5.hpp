#pragma once

#include "grammar.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <list>
#include <vector>

class Grammar5 : public Grammar
{
private:
    const std::vector<std::list<StackItem>> rightSideRules = {
        { Token(tLCurl), Nonterminal(nStatements), Token(tRCurl) },
        { Nonterminal(nStatement) },
        { Nonterminal(nStatement), Nonterminal(nStatements) },
        { Token(tEps) },
    };

public:
    ~Grammar5()
    {
    }

    std::list<StackItem> Expand(unsigned ruleNumber) override;
};