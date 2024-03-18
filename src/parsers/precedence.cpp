/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

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

void PrecedenceParser::Parse()
{
    this->initPrecedenceParsing();

    while (true) {
        this->inputToken = inputTape.front();
        if (this->inputToken == nullptr) {
            this->clearStack();
            throw InternalErrorException("Nullptr in inputTape.\n");
        }

        if (*this->inputToken == tFuncName) {
            this->insertFunctionEnd();
            this->saveFunctionContext();
            this->functionCounter++;
            throw ChangeParser();
        }

        if (this->parseIsSuccessful()) {
            this->cleanUpAfterParsing();
            break; // while
        }

        Token* firstToken = this->findFirstTokenInStack();
        switch ((*this->table)[*firstToken][*this->inputToken]) {
            case '=': {
                this->analysisPushdown.push_front(new Token(*this->inputToken));
                delete this->inputToken;
                break; // switch
            }
            case '<': {
                this->push();
                break; // switch
            }
            case '>': {
                this->reduce();
                break; // switch
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
}

void PrecedenceParser::findFirstRule(Rule& emptyRule)
{
    // push to list until stack.top is precedence symbol '<' or '$'
    for (auto it = this->analysisPushdown.begin(); it != this->analysisPushdown.end(); it++) {
        // if its precendence symbol '<' then just return
        StackItem* tmpItem = *it;
        if (typeid(*tmpItem) == typeid(PrecedenceSymbol)) {
            PrecedenceSymbol* tmpSymbol = dynamic_cast<PrecedenceSymbol*>(tmpItem);
            if (tmpSymbol == nullptr) {
                throw InternalErrorException("PrecedenceParser::findFirstRule: Dynamic cast failed - real type:" + std::string(typeid(*tmpItem).name()));
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
            if (typeid(*tmpItem) == typeid(Token)) {
                Token* tmpToken = dynamic_cast<Token*>(tmpItem);
                if (tmpToken == nullptr) {
                    throw InternalErrorException("PrecedenceParser::findFirstRule: Dynamic cast failed - real type:" + std::string(typeid(*tmpItem).name()));
                }

                if (*tmpToken == tExpEnd) {
                    break;
                }
                // else its part of rule, push it to the list (will be checked outside of this method)
                emptyRule.push_front(new Token(*tmpToken));
            }
            else { // typeid(*tmpItem) == typeid(Nonterminal)
                // implies for nonterminals as well
                Nonterminal* tmpNT = dynamic_cast<Nonterminal*>(tmpItem);
                if (tmpNT == nullptr) {
                    throw InternalErrorException("PrecedenceParser::findFirstRule: Dynamic cast failed - real type:" + std::string(typeid(*tmpItem).name()));
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
        StackItem* tmpItem = *it;
        if (typeid(*tmpItem) == typeid(Token)) {
            tmpExp = tmpItem;
            break;
        }
    }

    Token* toReturn = dynamic_cast<Token*>(tmpExp);
    if (toReturn == nullptr) {
        throw InternalErrorException("First token in stack is not token.\n");
    }

    return toReturn;
}


bool PrecedenceParser::parseIsSuccessful()
{
    // Only $E left on stack
    if (this->analysisPushdown.size() != 2) {
        return false;
    }
    StackItem* top = this->analysisPushdown.front();
    this->analysisPushdown.pop_front();
    StackItem* second = this->analysisPushdown.front();
    this->analysisPushdown.push_front(top);

    return (*this->inputToken == tExpEnd && *second == Token(tExpEnd) && *top == Nonterminal(nExpression));
}

void PrecedenceParser::insertExpressionEnd() const
{
    int counter = 0;
    // find first non-expression token occurence and insert tExpEnd before it
    for (auto token = inputTape.begin(); token != inputTape.end(); token++) {
        // if token is comma or semicolon, insert tExpEnd before it

        if (**token == tSemi || **token == tComma) {
            inputTape.insert(token, new Token(tExpEnd));
            return;
        }

        // insert tExpEnd before the first right parenthesis that is not matched with left parenthesis
        if (**token == tLPar) {
            counter++;
        }
        else if (**token == tRPar) {
            counter--;
        }

        if (counter < 0) {
            inputTape.insert(token, new Token(tExpEnd));
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
    StackItem* tmpStackTop = this->analysisPushdown.front();
    if (typeid(*tmpStackTop) == typeid(Nonterminal)) {
        this->analysisPushdown.push_front(new PrecedenceSymbol(Push));
        return;
    }
    this->analysisPushdown.pop_front();
    this->analysisPushdown.push_front(new PrecedenceSymbol(Push));
    this->analysisPushdown.push_front(tmpStackTop);
}

void PrecedenceParser::insertFunctionEnd()
{
    // go through inputTape and insert tFuncEnd after the first right parenthesis matched with left parenthesis
    int counter = 0;
    for (auto token = inputTape.begin(); token != inputTape.end(); token++) {
        if (**token == tLPar) {
            counter++;
        }
        else if (**token == tRPar) {
            counter--;
        }

        if (counter == 0 && **token == tRPar) {
            inputTape.insert(++token, new Token(tFuncEnd));
            return;
        }
    }
}

void PrecedenceParser::reduce()
{
    Rule tmpRule;
    this->findFirstRule(tmpRule);
    Grammar4 grammar;
    if (grammar.IsRule(tmpRule)) {
        this->logger = Logger::GetInstance();
        this->logger->AddRightSide(tmpRule);

        for (unsigned i = 0; i < tmpRule.size() + 1 /* Pop rule and '<' */; i++) {
            delete this->analysisPushdown.front();
            this->analysisPushdown.pop_front();
        }
        Nonterminal* toPush = new Nonterminal(nExpression);
        this->analysisPushdown.push_front(toPush);

        this->logger->AddLeftSide(toPush);
        this->logger->PrintRule();
        for (StackItem* item: tmpRule) {
            delete item;
        }
        return;
    }
    else {
        this->clearStack();
        for (StackItem* item: tmpRule) {
            delete item;
        }
        throw SyntaxErrorException("Sequence of tokens is not a rule.\n");
    }
}

void PrecedenceParser::initPrecedenceParsing()
{
    this->inputToken = inputTape.front();
    if (this->functionCounter <= 0 && *this->inputToken != tFuncEnd) {
        this->insertExpressionEnd();
        this->analysisPushdown.push_front(new Token(tExpEnd));
    }
    else if (*this->inputToken == tFuncEnd) {
        delete this->inputToken;
        inputTape.pop_front();
        inputTape.push_front(new Token(tConst));
        this->functionCounter--;
    }
}

void PrecedenceParser::cleanUpAfterParsing()
{
    this->clearStack();
    delete this->inputToken;
    inputTape.pop_front();
    delete this->pushdown.front();
    this->pushdown.pop_front();
}

void PrecedenceParser::push()
{
    this->pushPrecedence();
    this->analysisPushdown.push_front(new Token(*this->inputToken));
    delete this->inputToken;
    inputTape.pop_front();
}

void PrecedenceParser::saveFunctionContext()
{
    FunctionContext tmpContext;
    int counter = 0;
    for (auto token = inputTape.begin(); token != inputTape.end(); token++) {
        if (**token == tFuncName) {
            counter++;
        }
        else if (**token == tFuncEnd) {
            counter--;
        }

        if (counter <= 0) {
            break;
        }

        tmpContext.push_back(*token);
    }
    this->functionContexts.push(tmpContext);
}