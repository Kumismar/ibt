#include "grammar_2.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<std::list<StackItem*>> Grammar2::rightSideRules = {
    { new Token(tIf), new Token(tLPar), new Nonterminal(nExpression), new Token(tRPar), new Nonterminal(nCodeBlock), new Nonterminal(nIf2) },
    { new Token(tWhile), new Token(tLPar), new Nonterminal(nExpression), new Token(tRPar), new Nonterminal(nCodeBlock) },
    { new Token(tFor), new Token(tLPar), new Nonterminal(nExpression), new Token(tSemi), new Nonterminal(nExpression), new Token(tSemi), new Nonterminal(nExpression), new Token(tRPar), new Nonterminal(nCodeBlock) },
    { new Nonterminal(nExpression), new Token(tSemi) },
    { new Token(tReturn), new Nonterminal(nReturnExp) },
    { new Nonterminal(nCodeBlock) },
    { new Token(tSemi) },
    { new Token(tElseif), new Token(tLPar), new Nonterminal(nExpression), new Token(tRPar), new Nonterminal(nCodeBlock), new Nonterminal(nIf2) },
    { new Token(tElse), new Nonterminal(nCodeBlock) },
    { new Token(tEps) },
    { new Nonterminal(nExpression) },
    { new Token(tEps) },
};

std::list<StackItem*> Grammar2::Expand(unsigned ruleNumber)
{
    std::list<StackItem*> toReturn = Grammar2::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

void Grammar2::Cleanup()
{
    for (const std::list<StackItem*>& rule: rightSideRules) {
        for (StackItem* member: rule) {
            delete member;
        }
    }
}