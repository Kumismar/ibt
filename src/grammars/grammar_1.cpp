#include "grammar_1.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<Rule> Grammar1::rightSideRules = {
    { new Nonterminal(nStatement), new Nonterminal(nStatementList) },
    { new Nonterminal(nFunctionDef), new Nonterminal(nStatementList) },
    { new Nonterminal(nStatement), new Nonterminal(nStatementList) },
    { new Nonterminal(nFunctionDef), new Nonterminal(nStatementList) },
    { new Token(tEps) }
};

Rule Grammar1::Expand(unsigned ruleNumber)
{
    Rule toReturn = Grammar1::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

void Grammar1::Cleanup()
{
    for (const Rule& rule: rightSideRules) {
        for (StackItem* member: rule) {
            delete member;
        }
    }
}