#include "precedence.hpp"
#include "change_parser.hpp"
#include "grammar_4.hpp"
#include "internal_error.hpp"
#include "logger.hpp"
#include "nonterminal.hpp"
#include "parser.hpp"
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
    this->analysisPushdown.push_front(new Token(tExpEnd));

    while (true) {
        Token* inputToken = inputTape.front();
        if (inputToken == nullptr) {
            this->clearStack();
            throw InternalErrorException("Nullptr in inputTape.\n");
        }

        if (inputToken->GetTokenType() == tFuncName) {
            this->clearStack();
            throw ChangeParser();
        }

        if (this->parseIsSuccessful(*inputToken)) {
            this->clearStack();
            delete inputToken;
            break; // while
        }

        Token* firstToken = this->findFirstTokenInStack();
        switch (table[*firstToken][*inputToken]) {
            case '=': {
                this->analysisPushdown.push_front(new Token(*inputToken));
                delete inputToken;
                break; // switch
            }
            case '<': {
                this->pushPrecedence();
                this->analysisPushdown.push_front(new Token(*inputToken));
                delete inputToken;
                inputTape.pop_front();
                break; // switch
            }
            case '>': {
                Rule tmpRule;
                this->findFirstRule(tmpRule);
                Grammar4 grammar;
                if (grammar.IsRule(tmpRule)) {
                    logger = Logger::GetInstance();
                    logger->AddRightSide(tmpRule);

                    for (unsigned i = 0; i < tmpRule.size() + 1 /* Pop rule and '<' */; i++) {
                        delete this->analysisPushdown.front();
                        this->analysisPushdown.pop_front();
                    }
                    Nonterminal* toPush = new Nonterminal(nExpression);
                    this->analysisPushdown.push_front(toPush);

                    logger->AddLeftSide(toPush);
                    logger->PrintRule();
                    for (StackItem* item: tmpRule) {
                        delete item;
                    }
                    break; // switch
                }
                else {
                    this->clearStack();
                    for (StackItem* item: tmpRule) {
                        delete item;
                    }
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
    delete this->pushdown.front();
    this->pushdown.pop_front();
}

void PrecedenceParser::findFirstRule(Rule& emptyRule)
{
    // push to list until stack.top is precedence symbol '<' or '$'
    for (auto it = this->analysisPushdown.begin(); it != this->analysisPushdown.end(); it++) {
        // if its precendence symbol '<' then just return
        if ((*it)->GetItemType() == PrecSymbol_t) {
            PrecedenceSymbol* tmpSymbol = dynamic_cast<PrecedenceSymbol*>(*it);
            if (tmpSymbol == nullptr) {
                throw InternalErrorException("PrecedenceParser::findFirstRule: Dynamic cast failed - real type:" + std::string(typeid(*it).name()));
            }

            if (*tmpSymbol == Push) {
                break;
            }
            else {
                throw InternalErrorException("Different precedence symbol than '<' on the stack.\n");
            }
        }
        else {
            // if its token '$' then end of stack has been reached and just return
            if ((*it)->GetItemType() == Token_t) {
                Token* tmpToken = dynamic_cast<Token*>(*it);
                if (tmpToken == nullptr) {
                    throw InternalErrorException("PrecedenceParser::findFirstRule: Dynamic cast failed - real type:" + std::string(typeid(*it).name()));
                }

                if (*tmpToken == tExpEnd) {
                    break;
                }
                // else its part of rule, push it to the list (will be checked outside of this method)
                emptyRule.push_front(new Token(*tmpToken));
            }
            else {
                // implies for nonterminals as well
                Nonterminal* tmpNT = dynamic_cast<Nonterminal*>(*it);
                if (tmpNT == nullptr) {
                    throw InternalErrorException("PrecedenceParser::findFirstRule: Dynamic cast failed - real type:" + std::string(typeid(*it).name()));
                }
                emptyRule.push_front(new Nonterminal(*tmpNT));
            }
        }

        if (this->analysisPushdown.empty()) {
            throw InternalErrorException("ExpStack empty when finding first rule");
        }
    }
}

Token* PrecedenceParser::findFirstTokenInStack()
{
    StackItem* tmpExp = nullptr;
    for (auto it = this->analysisPushdown.begin(); it != this->analysisPushdown.end(); it++) {
        if ((*it)->GetItemType() == Token_t) {
            tmpExp = *it;
            break;
        }
    }

    Token* toReturn = dynamic_cast<Token*>(tmpExp);
    if (toReturn == nullptr) {
        throw InternalErrorException("First token in stack is not token.\n");
    }

    return toReturn;
}


bool PrecedenceParser::parseIsSuccessful(Token& inputToken)
{
    // Only $E left on stack
    if (this->analysisPushdown.size() != 2) {
        return false;
    }
    StackItem* top = this->analysisPushdown.front();
    this->analysisPushdown.pop_front();
    StackItem* second = this->analysisPushdown.front();
    this->analysisPushdown.push_front(top);

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
        delete this->analysisPushdown.front();
        this->analysisPushdown.pop_front();
    }
}


void PrecedenceParser::pushPrecedence()
{
    // Check if there is nonterminal on top of the stack, push to first or second position
    if (this->analysisPushdown.front()->GetItemType() != Nonterminal_t) {
        this->analysisPushdown.push_front(new PrecedenceSymbol(Push));
        return;
    }
    StackItem* tmp = this->analysisPushdown.front();
    this->analysisPushdown.pop_front();
    this->analysisPushdown.push_front(new PrecedenceSymbol(Push));
    this->analysisPushdown.push_front(tmp);
}