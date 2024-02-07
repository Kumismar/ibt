#include "grammar_1.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<std::list<StackItem>> Grammar1::rightSideRules = {
    { Nonterminal(nStatement), Nonterminal(nStatementList) },
    { Nonterminal(nFunctionDef), Nonterminal(nStatementList) },
    { Nonterminal(nStatement), Nonterminal(nStatementList) },
    { Nonterminal(nFunctionDef), Nonterminal(nStatementList) },
    { Token(tEps) }
};

std::list<StackItem> Grammar1::Expand(unsigned ruleNumber)
{
    std::list<StackItem> toReturn = Grammar1::rightSideRules[ruleNumber];
    toReturn.reverse();
    return toReturn;
}