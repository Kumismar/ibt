#include "grammar_2.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<std::list<StackItem>> Grammar2::rightSideRules = {
    { Token(tIf), Token(tLPar), Nonterminal(nExpression), Token(tRPar), Nonterminal(nCodeBlock), Nonterminal(nIf2) },
    { Token(tWhile), Token(tLPar), Nonterminal(nExpression), Token(tRPar), Nonterminal(nCodeBlock) },
    { Token(tFor), Token(tLPar), Nonterminal(nExpression), Token(tSemi), Nonterminal(nExpression), Token(tSemi), Nonterminal(nExpression), Token(tRPar), Nonterminal(nCodeBlock) },
    { Nonterminal(nVoluntaryType), Nonterminal(nExpression), Token(tAssign), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tSemi) },
    { Token(tReturn), Nonterminal(nReturnExp) },
    { Nonterminal(nCodeBlock) },
    { Token(tSemi) },
    { Token(tElseif), Token(tLPar), Nonterminal(nExpression), Token(tRPar), Nonterminal(nCodeBlock), Nonterminal(nIf2) },
    { Token(tElse), Nonterminal(nCodeBlock) },
    { Token(tEps) },
    { Token(tFuncName), Token(tLPar), Nonterminal(nArgs), Token(tRPar) },
    { Nonterminal(nExpression) },
    { Token(tEps) },
    { Nonterminal(nExpression), Nonterminal(nArgs2) },
    { Token(tEps) },
    { Token(tComma), Nonterminal(nArgs2), Nonterminal(nArgs) },

};

std::list<StackItem> Grammar2::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = Grammar2::rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}