#include "grammar_4.hpp"
#include "stack_item.hpp"
#include <list>
#include <stack>

const std::vector<std::list<Expression>> Grammar4::rightSideRules = {
    { Nonterminal(nExpression), Token(tPlus), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tMinus), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tMul), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tDiv), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tConcat), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tAnd), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tOr), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tEq), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tNEq), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tGreater), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tLess), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tGEq), Nonterminal(nExpression) },
    { Nonterminal(nExpression), Token(tLEq), Nonterminal(nExpression) },
    { Token(tExcl), Nonterminal(nExpression) },
    { Token(tMinus), Nonterminal(nExpression) },
    { Token(tVariable) },
    { Token(tConst) },
    { Token(tLPar), Nonterminal(nExpression), Token(tRPar) },
    { Nonterminal(nFunctionCall) }
};

std::list<StackItem> Grammar4::Expand(unsigned ruleNumber)
{
    return std::list<StackItem>{};
}