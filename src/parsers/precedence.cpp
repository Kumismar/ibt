#include "precedence.hpp"
#include "change_parser.hpp"
#include "grammar_4.hpp"
#include "internal_error.hpp"
#include "logger.hpp"
#include "nonterminal.hpp"
#include "precedence_symbol.hpp"
#include "precedence_table.hpp"
#include "stack_item.hpp"
#include "syntax_error.hpp"
#include "token.hpp"
#include <list>
#include <typeinfo>

void PrecedenceParser::Parse(InputTape& inputTape)
{
    PrecedenceTable table;
    Logger* logger;
    this->insertExpressionEnd(inputTape);
    this->analysisPushdown.push(new Token(tExpEnd));

    while (true) {
        Token* inputToken = inputTape.front();
        if (inputToken->GetTokenType() == tFuncName) {
            this->clearStack();
            throw ChangeParser();
        }

        if (this->parseIsSuccessful(*inputToken)) {
            break; // while
        }

        Token* firstToken = this->findFirstTokenInStack();
        switch (table[*firstToken][*inputToken]) {
            case '=': {
                analysisPushdown.push(new Token(inputToken->GetTokenType()));
                inputToken = inputTape.front();
                inputTape.pop_front();
                break; // switch
            }
            case '<': {
                this->pushPrecedence();
                analysisPushdown.push(new Token(inputToken->GetTokenType()));
                inputToken = inputTape.front();
                inputTape.pop_front();
                break; // switch
            }
            case '>': {
                std::list<StackItem*> tmpRule;
                this->findFirstRule(tmpRule);
                Grammar4 grammar;
                if (grammar.IsRule(tmpRule)) {
                    logger = Logger::GetInstance();
                    logger->AddRightSide(tmpRule);

                    for (unsigned i = 0; i < tmpRule.size() + 1 /* Pop rule and '<' */; i++) {
                        delete this->analysisPushdown.top();
                        this->analysisPushdown.pop();
                    }
                    Nonterminal* toPush = new Nonterminal(nExpression);
                    this->analysisPushdown.push(toPush);

                    logger->AddLeftSide(toPush);
                    logger->PrintRule();
                    break; // switch
                }
                else {
                    this->clearStack();
                    throw SyntaxErrorException("Sequence of tokens is not a rule.\n");
                }
            }
            case 'x': {
                this->clearStack();
                throw SyntaxErrorException("Invalid token.\n");
            }
            default: {
                this->clearStack();
                throw InternalErrorException("Something else than '<', '=', '>', 'x' in precedence table.\n");
            }
        }
    }
    inputTape.pop_front();
    this->clearStack();
    this->pushdown.pop();
}

void PrecedenceParser::findFirstRule(std::list<StackItem*>& emptyRule)
{
    std::stack<StackItem*> tmpStack;
    StackItem* tmpTop = this->analysisPushdown.top();
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
                if (*tmpToken == tExpEnd) {
                    break;
                }
                // else its part of rule, push it to the list (will be checked outside of this method)
                emptyRule.push_front(new Token(tmpToken->GetTokenType()));
            }
            else {
                // implies for nonterminals as well
                Nonterminal* tmpNT = dynamic_cast<Nonterminal*>(tmpTop);
                if (tmpNT == nullptr) {
                    throw InternalErrorException(typeid(*tmpTop).name());
                }
                emptyRule.push_front(new Nonterminal(tmpNT->GetNonterminalType()));
            }

            tmpStack.push(this->analysisPushdown.top());
            this->analysisPushdown.pop();
        }

        if (this->analysisPushdown.empty()) {
            throw InternalErrorException("ExpStack empty when finding first rule");
        }

        tmpTop = this->analysisPushdown.top();
    }

    while (!tmpStack.empty()) {
        this->analysisPushdown.push(tmpStack.top());
        tmpStack.pop();
    }
}

Token* PrecedenceParser::findFirstTokenInStack()
{
    std::stack<StackItem*> tmpStack;
    StackItem* tmpExp = this->analysisPushdown.top();
    while (tmpExp->GetItemType() != Token_t) {
        tmpStack.push(tmpExp);
        this->analysisPushdown.pop();
        tmpExp = this->analysisPushdown.top();
    }
    while (!tmpStack.empty()) {
        StackItem* tmpExp2 = tmpStack.top();
        tmpStack.pop();
        this->analysisPushdown.push(tmpExp2);
    }

    return dynamic_cast<Token*>(tmpExp);
}


bool PrecedenceParser::parseIsSuccessful(Token& inputToken)
{
    // Only $E left on stack
    if (this->analysisPushdown.size() != 2) {
        return false;
    }
    StackItem* top = this->analysisPushdown.top();
    this->analysisPushdown.pop();
    StackItem* second = this->analysisPushdown.top();
    this->analysisPushdown.push(top);

    return (inputToken == tExpEnd && *second == Token(tExpEnd) && *top == Nonterminal(nExpression));
}

void PrecedenceParser::insertExpressionEnd(InputTape& inputTape) const
{
    int counter = 0;
    // find first non-expression token occurence and insert tExpEnd before it
    for (auto it = inputTape.begin(); it != inputTape.end(); it++) {
        // if token is comma or semicolon, insert tExpEnd before it

        if (**it == tSemi || **it == tComma || **it == tEnd) {
            inputTape.insert(it, new Token(tExpEnd));
            return;
        }

        // insert tExpEnd before the first right parenthesis that is not matched with left parenthesis
        if (**it == tLPar) {
            counter++;
        }
        else if (**it == tRPar) {
            counter--;
        }

        if (counter < 0) {
            inputTape.insert(it, new Token(tExpEnd));
            return;
        }
    }
}

void PrecedenceParser::clearStack()
{
    while (!this->analysisPushdown.empty()) {
        delete this->analysisPushdown.top();
        this->analysisPushdown.pop();
    }
}


void PrecedenceParser::pushPrecedence()
{
    // Check if there is nonterminal on top of the stack, push to first or second position
    if (this->analysisPushdown.top()->GetItemType() != Nonterminal_t) {
        this->analysisPushdown.push(new PrecedenceSymbol(Push));
        return;
    }
    StackItem* tmp = this->analysisPushdown.top();
    this->analysisPushdown.pop();
    this->analysisPushdown.push(new PrecedenceSymbol(Push));
    this->analysisPushdown.push(tmp);
}