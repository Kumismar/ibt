#include "grammar_1.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<std::list<StackItem*>> Grammar1::rightSideRules = {
    { new Nonterminal(nStatement), new Nonterminal(nStatementList) },
    { new Nonterminal(nFunctionDef), new Nonterminal(nStatementList) },
    { new Nonterminal(nStatement), new Nonterminal(nStatementList) },
    { new Nonterminal(nFunctionDef), new Nonterminal(nStatementList) },
    { new Token(tEps) }
};

std::list<StackItem*> Grammar1::Expand(unsigned ruleNumber)
{
    std::list<StackItem*> toReturn = Grammar1::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

void Grammar1::Cleanup()
{
    for (const std::list<StackItem*>& rule: rightSideRules) {
        for (StackItem* member: rule) {
            delete member;
        }
    }
}