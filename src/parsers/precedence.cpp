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

void PrecedenceParser::Parse(std::list<Token>& inputTape)
{
    PrecedenceTable table;
    Logger* logger;
    this->insertExpressionEnd(inputTape);
    this->analysisPushdown.push(new Token(tExpEnd));

    while (!this->success) {
        Token& inputToken = inputTape.front();
        if (inputToken.GetTokenType() == tFuncName) {
            this->clearStack();
            throw ChangeParser();
        }
        inputTape.pop_front();

        if (this->parseIsSuccessful(inputToken)) {
            // TODO: pop ExpEnd token a nechat tam jen neterminal E
            break; // while
        }

        Token* firstToken = this->findFirstTokenInStack();
        switch (table[*firstToken][inputToken]) {
            case '=': {
                analysisPushdown.push(new Token(inputToken.GetTokenType()));
                inputToken = inputTape.front();
                break; // switch
            }
            case '<': {
                analysisPushdown.push(new PrecedenceSymbol('<'));
                analysisPushdown.push(new Token(inputToken.GetTokenType()));
                inputToken = inputTape.front();
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
                throw SyntaxErrorException("Invalid \n");
            }
            default: {
                this->clearStack();
                throw InternalErrorException("Something else than '<', '=', '>', 'x' in precedence table.\n");
            }
        }
    }
    this->clearStack();
    this->pushdown.pop();
}

void PrecedenceParser::findFirstRule(std::list<StackItem*>& emptyRule)
{
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
                if (tmpToken->GetTokenType() == tExpEnd) {
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

            this->analysisPushdown.pop();
        }

        if (this->analysisPushdown.empty()) {
            throw InternalErrorException("ExpStack empty when finding first rule");
        }

        tmpTop = this->analysisPushdown.top();
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

    return (inputToken == Token(tExpEnd) && *top == Token(tExpEnd) && *second == Nonterminal(nExpression));
}

void PrecedenceParser::insertExpressionEnd(std::list<Token>& inputTape) const
{
    inputTape.push_back(Token(tExpEnd));
}

void PrecedenceParser::clearStack()
{
    while (!this->analysisPushdown.empty()) {
        delete this->analysisPushdown.top();
        this->analysisPushdown.pop();
    }
}
