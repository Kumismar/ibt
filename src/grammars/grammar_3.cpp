/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-05-02 10:33
 */

#include "grammar_3.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"

const std::vector<Rule> Grammar3::rightSideRules = {
    { new Token(tFunction), new Token(tFuncName), new Token(tLPar), new Nonterminal(nParams), new Token(tRPar), new Token(tColon), new Nonterminal(nVoluntaryType), new Token(tLCurl), new Nonterminal(nStatements), new Nonterminal(nStop), new Token(tRCurl), new Nonterminal(nStop) },
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
        for (Symbol* member: rule) {
            delete member;
        }
    }
}