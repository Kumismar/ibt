#include "grammar_4.hpp"
#include "expression.hpp"
#include "nonterminal.hpp"
#include "token.hpp"
#include <list>
#include <pthread.h>

const std::vector<std::list<Expression*>> Grammar4::rightSideRules = {
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
    { new Token(tExcl), new Nonterminal(nExpression) },
    { new Token(tMinus), new Nonterminal(nExpression) },
    { new Nonterminal(nVoluntaryType), new Nonterminal(nExpression), new Token(tAssign), new Nonterminal(nExpression) },
    { new Token(tVariable) },
    { new Token(tConst) },
    { new Token(tFuncName), new Token(tLPar), new Nonterminal(nArgs), new Token(tRPar) },
    { new Token(tLPar), new Nonterminal(nExpression), new Token(tRPar) },
    { new Nonterminal(nExpression), new Nonterminal(nArgs2) },
    { new Token(tEps) },
    { new Token(tComma), new Nonterminal(nArgs2), new Nonterminal(nArgs) },
    { new Token(tEps) }
};

std::list<StackItem*> Grammar4::Expand(unsigned ruleNumber)
{
    return std::list<StackItem*>{};
}

bool Grammar4::IsRule(std::list<Expression*>& stackRule)
{
    // check all the possible rules for given sequence of tokens/nonterminals
    for (const auto& rule: Grammar4::rightSideRules) {
        if (rule.size() != stackRule.size()) {
            continue;
        }
        bool ruleMatch = true;
        // compare elements of grammar rule and the given sequence
        auto stackRuleMember = stackRule.cbegin();
        for (const Expression* ruleMember: rule) {
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
    for (const std::list<Expression*>& rule: rightSideRules) {
        for (Expression* member: rule) {
            delete member;
        }
    }
}