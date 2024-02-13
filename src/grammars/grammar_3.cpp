#include "grammar_3.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<std::list<StackItem*>> Grammar3::rightSideRules = {
    { new Token(tFunction), new Token(tFuncName), new Token(tLPar), new Nonterminal(nParams), new Token(tRPar), new Token(tColon), new Nonterminal(nFuncType), new Nonterminal(nCodeBlock) },
    { new Nonterminal(nType), new Token(tVariable), new Nonterminal(nParams2) },
    { new Token(tComma), new Nonterminal(nType), new Token(tVariable), new Nonterminal(nParams2) },
    { new Token(tEps) },
    { new Nonterminal(nType) },
    { new Token(tEps) }
};

std::list<StackItem*> Grammar3::Expand(unsigned ruleNumber)
{
    std::list<StackItem*> toReturn = Grammar3::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

void Grammar3::Cleanup()
{
    for (const std::list<StackItem*>& rule: rightSideRules) {
        for (StackItem* member: rule) {
            delete member;
        }
    }
}