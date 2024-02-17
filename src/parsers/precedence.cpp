#include "precedence.hpp"
#include "change_parser.hpp"
#include "grammar_4.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "precedence_symbol.hpp"
#include "precedence_table.hpp"
#include "stack_item.hpp"
#include "syntax_error.hpp"
#include "token.hpp"
#include <list>

void PrecedenceParser::Parse(std::list<Token>& inputTape)
{
    PrecedenceTable table;
    this->pushdown.push(new Token(tEnd));
    this->insertExpressionEnd(inputTape);

    while (!this->success) {
        Token& inputToken = inputTape.front();
        if (inputToken.GetTokenType() == tFuncName) {
            throw ChangeParser();
        }
        inputTape.pop_front();

        if (this->parseIsSuccessful(inputToken)) {
            this->success = true;
        }

        Token* firstToken = this->findFirstTokenInStack();
        switch (table[*firstToken][inputToken]) {
            case '=': {
                pushdown.push(new Token(inputToken.GetTokenType()));
                inputToken = inputTape.front();
                inputTape.pop_front();
                break;
            }
            case '<': {
                pushdown.push(new PrecedenceSymbol('<'));
                pushdown.push(&inputToken);
                inputToken = inputTape.front();
                inputTape.pop_front();
                break;
            }
            case '>': {
                std::list<StackItem*> tmpRule;
                this->findFirstRule(tmpRule);
                Grammar4 grammar;
                if (grammar.IsRule(tmpRule)) {
                    // TODO: print(rule)
                    for (unsigned i = 0; i < tmpRule.size() + 1 /* Pop rule and '<'*/; i++) {
                        this->pushdown.pop();
                    }
                    this->pushdown.push(new Nonterminal(nExpression));
                    break;
                }
                else {
                    throw SyntaxErrorException("Sequence of tokens is not a rule.\n");
                }
            }
            default: {
                throw InternalErrorException("Something else than '<', '=', '>' in precedence table.\n");
            }
        }
    }
}

void PrecedenceParser::findFirstRule(std::list<StackItem*>& emptyRule)
{
    StackItem* tmpTop = this->pushdown.top();
    // push to list until stack.top is precedence symbol '<' or '$'
    while (true) {
        // if its precendence symbol '<' then just return
        if (tmpTop->GetItemType() == PrecSymbol_t) {
            PrecedenceSymbol* tmpSymbol = dynamic_cast<PrecedenceSymbol*>(tmpTop);
            if (*tmpSymbol == Push) {
                break;
            }
            else {
                throw InternalErrorException("Different precedence symbol than '<' on the stack.\n");
            }
        }
        else {
            // if its token '$' then end of stack has been reached and just return
            if (tmpTop->GetItemType() == Token_t) {
                Token* tmpToken = dynamic_cast<Token*>(tmpTop);
                if (tmpToken->GetTokenType() == tEnd) {
                    break;
                }
                // else its part of rule, push it to the list (will be checked outside of this method)
                emptyRule.push_front(new Token(tmpToken->GetTokenType()));
            }
            else {
                // implies for nonterminals as well
                Nonterminal* tmpNT = dynamic_cast<Nonterminal*>(tmpTop);
                emptyRule.push_front(new Nonterminal(tmpNT->GetNonterminalType()));
            }

            this->pushdown.pop();
        }

        if (this->pushdown.empty()) {
            throw InternalErrorException("ExpStack empty when finding first rule");
        }

        tmpTop = this->pushdown.top();
    }
}

Token* PrecedenceParser::findFirstTokenInStack()
{
    // TODO: kontrola prazdnyho zasobniku
    std::stack<StackItem*> tmpStack;
    StackItem* tmpExp = this->pushdown.top();
    while (tmpExp->GetItemType() != Token_t) {
        tmpStack.push(tmpExp);
        this->pushdown.pop();
        tmpExp = this->pushdown.top();
    }
    while (!tmpStack.empty()) {
        StackItem* tmpExp2 = tmpStack.top();
        tmpStack.pop();
        this->pushdown.push(tmpExp2);
    }

    return dynamic_cast<Token*>(tmpExp);
}


bool PrecedenceParser::parseIsSuccessful(Token& inputToken)
{
    // Only $E left on stack
    if (this->pushdown.size() != 2) {
        return false;
    }
    StackItem* top = this->pushdown.top();
    this->pushdown.pop();
    StackItem* second = this->pushdown.top();
    this->pushdown.push(top);

    return (inputToken == Token(tEnd) && *top == Token(tEnd) && *second == Nonterminal(nExpression));
}

void PrecedenceParser::insertExpressionEnd(std::list<Token>& inputTape) const
{
    inputTape.push_back(Token(tEnd));
}