#include "grammar_3.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<std::list<StackItem>> Grammar3::rightSideRules = {
    { Token(tFunction), Token(tFuncName), Token(tLPar), Nonterminal(nParams), Token(tRPar), Token(tColon), Nonterminal(nFuncType), Nonterminal(nCodeBlock) },
    { Nonterminal(nType), Token(tVariable), Nonterminal(nParams2) },
    { Token(tComma), Nonterminal(nType), Token(tVariable), Nonterminal(nParams2) },
    { Token(tEps) },
    { Nonterminal(nType) },
    { Token(tEps) }
};

std::list<StackItem> Grammar3::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = Grammar3::rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}