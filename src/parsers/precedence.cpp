/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-22 22:14
 * @ Modified time: 2024-04-02 22:41
 */

#include "precedence.hpp"
#include "exception_base.hpp"
#include "function_parsed.hpp"
#include "grammar_4.hpp"
#include "internal_error.hpp"
#include "logger.hpp"
#include "nonterminal.hpp"
#include "precedence_symbol.hpp"
#include "predictive.hpp"
#include "stack_item.hpp"
#include "syntax_error.hpp"
#include "token.hpp"
#include <list>

PrecedenceParser::PrecedenceParser(AnalysisStack& stack)
    : pushdown(stack)
{
    this->table = new PrecedenceTable();
}

PrecedenceParser::~PrecedenceParser()
{
    delete this->table;
}

void PrecedenceParser::Parse()
{
    this->initPrecedenceParsing();

    while (true) {
        this->inputToken = inputTape.front();
        if (inputTape.empty() || this->inputToken == nullptr) {
            this->clearStack();
            throw SyntaxError("Missing token(s).\n");
        }

        if (*this->inputToken == tFuncName) {
            this->parseFunction();
        }

        if (this->parseIsSuccessful()) {
            this->cleanUpAfterParsing();
            break; // while
        }

        Token* firstToken = this->findFirstTokenInStack();
        switch ((*this->table)[*firstToken][*this->inputToken]) {
            case '=': {
                this->analysisPushdown.push_front(this->inputToken->Clone());
                delete this->inputToken;
                inputTape.pop_front();
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
                throw SyntaxError("Invalid token.\n");
            }
            default: {
                this->clearStack();
                throw InternalError("Something else than '<', '=', '>', 'x' in precedence table.\n");
            }
        }
    }
}

void PrecedenceParser::findFirstRule(Rule& emptyRule)
{
    // push to list until stack.top is precedence symbol '<' or '$'
    for (auto it = this->analysisPushdown.begin(); it != this->analysisPushdown.end(); it++) {
        Symbol* tmpItem = *it;
        switch (tmpItem->GetSymbolType()) {
            case PrecSymbol_t: {
                PrecedenceSymbol* tmpSymbol = dynamic_cast<PrecedenceSymbol*>(tmpItem);
                if (tmpSymbol == nullptr) {
                    throw InternalError("PrecedenceParser::findFirstRule: Dynamic cast to PrecedenceSymbol* failed - real type:" + std::string(typeid(*tmpItem).name()));
                }

                // if its precendence symbol '<' then just return
                if (*tmpSymbol == Push) {
                    return;
                }
                else {
                    throw InternalError("Different precedence symbol than '<' on the stack.\n");
                }
            }
            case Token_t: {
                Token* tmpToken = dynamic_cast<Token*>(tmpItem);
                if (tmpToken == nullptr) {
                    throw InternalError("PrecedenceParser::findFirstRule: Dynamic cast to Token* failed - real type:" + std::string(typeid(*tmpItem).name()));
                }

                // if its token '$' then end of stack has been reached and just return
                if (*tmpToken == tExpEnd) {
                    break;
                }
                // else its part of rule, push it
                emptyRule.push_front(new Token(*tmpToken));
                break;
            }
            case Nonterminal_t: {
                // implies for nonterminals as well
                Nonterminal* tmpNT = dynamic_cast<Nonterminal*>(tmpItem);
                if (tmpNT == nullptr) {
                    throw InternalError("PrecedenceParser::findFirstRule: Dynamic cast to Nonterminal* failed - real type:" + std::string(typeid(*tmpItem).name()));
                }
                emptyRule.push_front(new Nonterminal(*tmpNT));
                break;
            }
            default: {
                throw InternalError("PrecedenceParser::findFirstRule: Unexpected type on stack: " + std::string(typeid(*tmpItem).name()) + ".\n");
            }
        }

        if (this->analysisPushdown.empty()) {
            throw InternalError("ExpStack empty when finding first rule");
        }
    }
}

Token* PrecedenceParser::findFirstTokenInStack()
{
    Symbol* tmpExp = nullptr;
    for (auto it = this->analysisPushdown.begin(); it != this->analysisPushdown.end(); it++) {
        Symbol* tmpItem = *it;
        if (tmpItem->GetSymbolType() == Token_t) {
            tmpExp = tmpItem;
            break;
        }
    }

    Token* toReturn = dynamic_cast<Token*>(tmpExp);
    if (toReturn == nullptr) {
        throw InternalError("First token in stack is not token.\n");
    }

    return toReturn;
}


bool PrecedenceParser::parseIsSuccessful()
{
    // Only $E left on stack
    if (this->analysisPushdown.size() != 2) {
        return false;
    }
    Symbol* top = this->analysisPushdown.front();
    this->analysisPushdown.pop_front();
    Symbol* second = this->analysisPushdown.front();
    this->analysisPushdown.push_front(top);

    return (*this->inputToken == tExpEnd && *second == Token(tExpEnd) && *top == Nonterminal(nExpression));
}

void PrecedenceParser::insertExpressionEnd()
{
    auto token = inputTape.begin();
    while (token != inputTape.end()) {
        // skip operand
        this->skipOperand(token);

        // if the operand was the last one, insert expEnd behind
        if (!this->isOperator(**token)) {
            break;
        }
        // skip operator
        token++;
    }

    if (token == inputTape.end()) {
        throw SyntaxError("Missing token(s).\n");
    }

    inputTape.insert(token, new Token(tExpEnd));
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
    Symbol* tmpStackTop = this->analysisPushdown.front();
    if (tmpStackTop->GetSymbolType() != Nonterminal_t) {
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
    Grammar4* grammar = new Grammar4();
    if (grammar->IsRule(tmpRule)) {
        this->logger = Logger::GetInstance();
        tmpRule.reverse(); // For logging purpose only, the rest of grammars work with reversed string
        this->logger->AddRightSide(tmpRule);

        for (unsigned i = 0; i < tmpRule.size() + 1 /* Pop rule and '<' */; i++) {
            delete this->analysisPushdown.front();
            this->analysisPushdown.pop_front();
        }
        Nonterminal* toPush = new Nonterminal(nExpression);
        this->analysisPushdown.push_front(toPush);

        this->logger->AddLeftSide(toPush);
        this->logger->PrintRule();
        for (Symbol* item: tmpRule) {
            delete item;
        }
        delete grammar;
        return;
    }
    else {
        this->clearStack();
        for (Symbol* item: tmpRule) {
            delete item;
        }
        delete grammar;
        throw SyntaxError("Invalid token.\n");
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
    this->analysisPushdown.push_front(this->inputToken->Clone());
    Logger::GetInstance()->AddTokenToRecents(*this->inputToken);
    delete this->inputToken;
    inputTape.pop_front();
}

void PrecedenceParser::initPrecedenceParsing()
{
    this->analysisPushdown.push_front(new Token(tExpEnd));
    this->insertExpressionEnd();
}

void PrecedenceParser::skipOperand(InputTape::iterator& token)
{
    // skip unary operators
    while (**token == tUnMinus || **token == tExcl) {
        token++;
        if (token == inputTape.end()) {
            throw SyntaxError("Missing token(s).\n");
        }
    }

    if (**token == tLPar) {
        this->skipOperandInParentheses(token);
        return;
    }

    if (**token == tFuncName) {
        this->skipFunctionCall(token);
        return;
    }

    if (**token != tConst && **token != tVariable) {
        throw SyntaxError("Invalid token.\n");
    }

    token++;
    if (token == inputTape.end()) {
        throw SyntaxError("Missing token(s).\n");
    }
}

void PrecedenceParser::skipFunctionCall(InputTape::iterator& token)
{
    int counter = 0;

    for (token++; (token != inputTape.end() && **token != tExpEnd); token++) {
        if (**token == tLPar) {
            counter++;
        }
        else if (**token == tRPar) {
            counter--;
        }

        if (counter == 0) {
            token++;
            return;
        }
    }

    if (token == inputTape.end() || **token == tExpEnd) {
        throw SyntaxError("Invalid token.\n");
    }
}

void PrecedenceParser::skipOperandInParentheses(InputTape::iterator& token)
{
    int counter = 0;
    while (token != inputTape.end()) {
        if (**token == tLPar) {
            counter++;
        }
        else if (**token == tRPar) {
            counter--;
        }

        if (counter == 0) {
            break;
        }

        token++;
    }

    token++;
    if (token == inputTape.end()) {
        throw SyntaxError("Missing token(s).\n");
    }
}

bool PrecedenceParser::isOperator(Token& token)
{
    return (token == tPlus || token == tMinus || token == tMul || token == tDiv || token == tConcat ||
            token == tAnd || token == tOr ||
            token == tEq || token == tNEq || token == tLess || token == tGreater || token == tLEq || token == tGEq ||
            token == tAssign);
}

void PrecedenceParser::parseFunction()
{
    this->insertFunctionEnd();
    PredictiveParser* predParser = new PredictiveParser(this->pushdown);
    try {
        predParser->Parse(true);
    }
    catch (FunctionParsed const& e) {
        delete predParser;
        this->inputToken = inputTape.front();
    }
    catch (...) {
        delete predParser;
        throw;
    }
}
