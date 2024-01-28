#pragma once

#include "grammar.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <list>
#include <vector>

class Grammar3 : public Grammar
{
private:
    const std::vector<std::list<StackItem>> rightSideRules = {
        { Token(tFunction), Token(tFuncName), Token(tLPar), Nonterminal(nParams), Token(tRPar), Token(tColon), Nonterminal(nFuncType), Nonterminal(nCodeBlock) },
        { Nonterminal(nType), Token(tVariable), Nonterminal(nParams2) },
        { Token(tComma), Nonterminal(nType), Token(tVariable), Nonterminal(nParams2) },
        { Token(tEps) },
        { Nonterminal(nType) },
        { Token(tEps) }
    };

public:
    ~Grammar3()
    {
    }

    std::list<StackItem> Expand(unsigned ruleNumber) override;
};