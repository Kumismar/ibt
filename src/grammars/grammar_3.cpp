/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#include "grammar_3.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"

const std::vector<Rule> Grammar3::rightSideRules = {
    { new Token(tFunction), new Token(tFuncName), new Token(tLPar), new Nonterminal(nParams), new Token(tRPar), new Token(tColon), new Nonterminal(nVoluntaryType), new Token(tLCurl), new Nonterminal(nStatements), new Token(tRCurl) },
    { new Nonterminal(nType), new Token(tVariable), new Nonterminal(nParams2) },
    { new Token(tEps) },
    { new Token(tComma), new Nonterminal(nType), new Token(tVariable), new Nonterminal(nParams2) },
    { new Token(tEps) },
};

Rule Grammar3::Expand(unsigned ruleNumber)
{
    Rule toReturn = Grammar3::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

void Grammar3::Cleanup()
{
    for (const Rule& rule: rightSideRules) {
        for (StackItem* member: rule) {
            delete member;
        }
    }
}