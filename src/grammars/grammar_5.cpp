#include "grammar_5.hpp"
#include "stack_item.hpp"
#include <list>

const std::vector<Rule> Grammar5::rightSideRules = {
    { new Token(tLCurl), new Nonterminal(nStatements), new Token(tRCurl) },
    { new Nonterminal(nStatement) },
    { new Nonterminal(nStatement), new Nonterminal(nStatements) },
    { new Token(tEps) }
};

Rule Grammar5::Expand(unsigned ruleNumber)
{
    Rule toReturn = Grammar5::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

void Grammar5::Cleanup()
{
    for (const Rule& rule: rightSideRules) {
        for (StackItem* member: rule) {
            delete member;
        }
    }
}