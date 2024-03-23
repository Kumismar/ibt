/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-23 17:33
 */

#include "grammar_2.hpp"
#include "nonterminal.hpp"
#include "stack_item.hpp"
#include "token.hpp"

const std::vector<Rule> Grammar2::rightSideRules = {
    { new Token(tIf), new Token(tLPar), new Nonterminal(nExpression), new Token(tRPar), new Nonterminal(nCodeBlock), new Nonterminal(nIf2) },
    { new Token(tWhile), new Token(tLPar), new Nonterminal(nExpression), new Token(tRPar), new Nonterminal(nCodeBlock) },
    { new Token(tFor), new Token(tLPar), new Nonterminal(nDeclOrExpr), new Token(tSemi), new Nonterminal(nExpression), new Token(tSemi), new Nonterminal(nExpression), new Token(tRPar), new Nonterminal(nCodeBlock) },
    { new Nonterminal(nDeclOrExpr), new Token(tSemi) },
    { new Nonterminal(nCodeBlock) },
    { new Token(tReturn), new Nonterminal(nReturnExp), new Token(tSemi) },
    { new Token(tSemi) },
    { new Token(tElseif), new Token(tLPar), new Nonterminal(nExpression), new Token(tRPar), new Nonterminal(nCodeBlock), new Nonterminal(nIf2) },
    { new Token(tElse), new Nonterminal(nCodeBlock) },
    { new Token(tEps) },
    { new Nonterminal(nType), new Token(tVariable), new Token(tAssign), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression) },
    { new Nonterminal(nExpression) },
    { new Token(tEps) },
};

Rule Grammar2::Expand(unsigned ruleNumber)
{
    Rule toReturn = Grammar2::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

void Grammar2::Cleanup()
{
    for (const Rule& rule: rightSideRules) {
        for (Symbol* member: rule) {
            delete member;
        }
    }
}