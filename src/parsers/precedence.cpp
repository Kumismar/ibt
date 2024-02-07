#include "precedence.hpp"
#include "empty_stack.hpp"
#include "grammar_4.hpp"
#include "invalid_symbol.hpp"
#include "precedence_symbol.hpp"
#include "precedence_table.hpp"

void PrecedenceParser::Parse(std::list<Token>& inputTape)
{
    PrecedenceTable table;
    this->expStack.push(Token(tEnd));
    do {
        this->top = expStack.top();
        Token& inputToken = inputTape.front();
        inputTape.pop_front();

        Token& firstToken = this->findFirstTokenInStack();
        switch (table[firstToken][inputToken]) {
            case '=': {
                expStack.push(inputToken);
                inputToken = inputTape.front();
                inputTape.pop_front();
                break;
            }
            case '<': {
                expStack.push(PrecedenceSymbol('<'));
                expStack.push(inputToken);
                inputToken = inputTape.front();
                inputTape.pop_front();
                break;
            }
            case '>': {
                try {
                    std::list<Expression> tmpRule;
                    this->findFirstRule(tmpRule);
                    Grammar4 grammar;
                    if (grammar.IsRule(tmpRule)) {
                        // TODO: dodelat algoritmus, print(rule)
                        // stack.pop(<y)
                        // stack.push(A)
                    }
                    else {
                        // TODO: chyba;
                    }
                }
                // TODO: exception handling
                catch (InvalidSymbolException const& e) {
                }
                catch (EmptyStackException const& e) {
                }
            }
        }

    } while (!this->success && !this->fail);
}

void PrecedenceParser::findFirstRule(std::list<Expression>& emptyRule)
{
    Expression& tmpTop = this->expStack.top();
    // push to list until stack.top is precedence symbol '<' or '$'
    while (true) {
        // if its precendence symbol '<' then just return
        if (tmpTop.GetExpressionType() == ExpPrecSymbol) {
            PrecedenceSymbol& tmpSymbol = dynamic_cast<PrecedenceSymbol&>(tmpTop);
            if (tmpSymbol == Push) {
                break;
            }
            else {
                throw InvalidSymbolException("");
            }
        }
        else {
            // if its token '$' then end of stack has been reached and just return
            if (tmpTop.GetExpressionType() == ExpToken) {
                Token& tmpToken = dynamic_cast<Token&>(tmpTop);
                if (tmpToken.GetTokenType() == tEnd) {
                    break;
                }
            }
            // else its part of rule, push it to the list (will be checked outside of this method)
            emptyRule.push_front(tmpTop);
            this->expStack.pop();
        }

        if (this->expStack.empty()) {
            throw EmptyStackException("");
        }

        tmpTop = this->expStack.top();
    }
}

Token& PrecedenceParser::findFirstTokenInStack()
{
    // TODO: kontrola prazdnyho zasobniku
    std::stack<Expression> tmpStack;
    Expression& tmpExp = this->expStack.top();
    while (tmpExp.GetExpressionType() != ExpToken) {
        tmpStack.push(tmpExp);
        this->expStack.pop();
        tmpExp = this->expStack.top();
    }
    while (!tmpStack.empty()) {
        Expression tmpExp2 = tmpStack.top();
        tmpStack.pop();
        this->expStack.push(tmpExp2);
    }

    return dynamic_cast<Token&>(tmpExp);
}