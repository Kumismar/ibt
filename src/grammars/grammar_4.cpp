/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-05-02 10:33
 */

#include "grammar_4.hpp"
#include "nonterminal.hpp"
#include "token.hpp"
#include <list>

const std::vector<Rule> Grammar4::rightSideRules = {
    { new Nonterminal(nExpression), new Token(tPlus), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tMinus), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tMul), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tDiv), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tConcat), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tAnd), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tOr), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tEq), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tNEq), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tGreater), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tLess), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tGEq), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tLEq), new Nonterminal(nExpression) },
    { new Nonterminal(nExpression), new Token(tAssign), new Nonterminal(nExpression) },
    { new Token(tExcl), new Nonterminal(nExpression) },
    { new Token(tUnMinus), new Nonterminal(nExpression) },
    { new Token(tVariable) },
    { new Token(tConst) },
    { new Token(tFuncName), new Token(tLPar), new Nonterminal(nArgs), new Token(tRPar) },
    { new Token(tLPar), new Nonterminal(nExpression), new Token(tRPar) },
    { new Nonterminal(nExpression), new Nonterminal(nArgs2) },
    { new Token(tEps) },
    { new Token(tComma), new Nonterminal(nExpression), new Nonterminal(nArgs2) },
    { new Token(tEps) },
    // A special rule for function call - this is pushed into inputTape as temporary token for precedence parser
    { new Token(tFuncConst) }
};


Rule Grammar4::Expand(unsigned ruleNumber)
{
    Rule toReturn = Grammar4::rightSideRules[ruleNumber - 1];
    toReturn.reverse();
    return toReturn;
}

bool Grammar4::IsRule(Rule& stackRule)
{
    // check all the possible rules for given sequence of tokens/nonterminals
    for (const auto& rule: Grammar4::rightSideRules) {
        if (rule.size() != stackRule.size()) {
            continue;
        }
        bool ruleMatch = true;
        // compare elements of grammar rule and the given sequence
        auto stackRuleMember = stackRule.cbegin();
        for (const Symbol* ruleMember: rule) {
            // if one pair is not equal, continue with next rule
            if (*ruleMember != **stackRuleMember) {
                ruleMatch = false;
                break;
            }
            stackRuleMember++;
        }
        if (ruleMatch) {
            return true;
        }
    }
    return false;
}

void Grammar4::Cleanup()
{
    for (const Rule& rule: rightSideRules) {
        for (Symbol* member: rule) {
            delete member;
        }
    }
}