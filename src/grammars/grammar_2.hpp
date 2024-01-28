#pragma once

#include "grammar.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <list>
#include <vector>

class Grammar2 : public Grammar
{
private:
    const std::vector<std::list<StackItem>> rightSideRules = {
        { Token(tIf), Token(tLPar), Nonterminal(nExpression), Token(tRPar), Nonterminal(nCodeBlock), Nonterminal(nIf2) },
        { Token(tWhile), Token(tLPar), Nonterminal(nExpression), Token(tRPar), Nonterminal(nCodeBlock) },
        { Token(tFor), Token(tLPar), Nonterminal(nExpression), Token(tSemi), Nonterminal(nExpression), Token(tSemi), Nonterminal(nExpression), Token(tRPar), Nonterminal(nCodeBlock) },
        { Nonterminal(nExpression), Token(tSemi) },
        { Token(tReturn), Nonterminal(nReturnExp) },
        { Nonterminal(nCodeBlock) },
        { Token(tSemi) },
        { Token(tElseif), Token(tLPar), Nonterminal(nExpression), Token(tRPar), Nonterminal(nCodeBlock), Nonterminal(nIf2) },
        { Token(tElse), Nonterminal(nCodeBlock) },
        { Token(tEps) },
        { Nonterminal(nExpression) },
        { Token(tEps) }
    };

public:
    ~Grammar2()
    {
    }

    std::list<StackItem> Expand(unsigned ruleNumber) override;
};