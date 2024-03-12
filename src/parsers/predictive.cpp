#include "predictive.hpp"
#include "analysis_success.hpp"
#include "change_parser.hpp"
#include "grammar_factory.hpp"
#include "internal_error.hpp"
#include "logger.hpp"
#include "stack_item.hpp"
#include "syntax_error.hpp"
#include "token.hpp"

PredictiveParser::PredictiveParser(AnalysisStack& stack)
    : pushdown(stack)
{
    this->table = new LLTable();
}

PredictiveParser::~PredictiveParser()
{
    delete table;
}

void PredictiveParser::Parse()
{
    while (true) {
        this->stackTop = this->pushdown.front();
        if (inputTape.empty()) {
            throw SyntaxErrorException("Missing token(s).\n");
        }
        this->inputToken = inputTape.front();

        switch (this->stackTop->GetItemType()) {
            // Case T or $:
            case Token_t: {
                this->parseToken();
                break;
            }
            // Case N:
            case Nonterminal_t: {
                this->parseNonterminal();
                break;
            }
            default: {
                throw InternalErrorException("Unexpected item type: " + std::string(typeid(*this->stackTop).name()) + "\n");
            }
        }
    }
}

bool PredictiveParser::returnedEpsilon(Rule& expandedRule)
{
    if (expandedRule.size() == 1 && expandedRule.front()->GetItemType() == Token_t) {
        Token* t = dynamic_cast<Token*>(expandedRule.front());
        return *t == tEps;
    }
    return false;
}

void PredictiveParser::InitSyntaxAnalysis()
{
    this->pushdown.push_front(new Token(tEnd));
    this->pushdown.push_front(new Nonterminal(nProgram));
}


void PredictiveParser::ClearStack()
{
    if (!this->pushdown.empty()) {
        for (const auto& item: this->pushdown) {
            delete item;
        }
        this->pushdown.clear();
    }
}

void PredictiveParser::parseNonterminal()
{
    Nonterminal* stackNT = dynamic_cast<Nonterminal*>(this->stackTop);
    if (stackNT == nullptr) {
        throw InternalErrorException("Dynamic cast to Nonterminal* failed\n");
    }

    // Expression => give control to precedence parser
    if (stackNT->GetNonterminalType() == nExpression) {
        if (*this->inputToken != tFuncName) {
            throw ChangeParser();
        }

        if (this->functionCounter <= 0) {
            throw ChangeParser();
        }
    }

    LLTableIndex tableItem = (*this->table)[*stackNT][*this->inputToken];
    // Rule exists -> pop old nonterminal, expand it and push new string to the stack
    if (tableItem != LLTableIndex({ 0, 0 })) {
        Logger* logger = Logger::GetInstance();
        logger->AddLeftSide(this->stackTop);
        Grammar* grammar = GrammarFactory::CreateGrammar(tableItem.grammarNumber);

        delete this->pushdown.front();
        this->pushdown.pop_front();

        Rule expandedRule = grammar->Expand(tableItem.ruleNumber);
        logger->AddRightSide(expandedRule);

        // if right side is not epsilon, it will be pushed
        if (!this->returnedEpsilon(expandedRule)) {
            for (StackItem* item: expandedRule) {
                this->pushdown.push_front(item->Clone());
            }
        }

        logger->PrintRule();
        delete grammar;
    }
    else {
        throw SyntaxErrorException("Rule not found in LL table\n");
    }
}

void PredictiveParser::parseToken()
{
    Token* stackToken = dynamic_cast<Token*>(this->stackTop);
    if (stackToken == nullptr) {
        throw InternalErrorException("Dynamic cast to Token* failed\n");
    }

    // Case $:
    if (stackToken->GetTokenType() == tEnd) {
        this->parseEnd();
    }

    // Case T:
    if (*this->inputToken == tFuncEnd) {
        this->functionCounter--;
        throw ChangeParser();
    }

    if (*this->inputToken == tExpEnd) {
        delete this->inputToken;
        inputTape.pop_front();
        throw ChangeParser();
    }

    if (*stackToken == *this->inputToken) {
        delete this->inputToken;
        delete this->pushdown.front();
        this->pushdown.pop_front();
        inputTape.pop_front();
    }
    else {
        throw SyntaxErrorException("Unexpected token.\n");
    }
}

void PredictiveParser::parseEnd()
{
    if (this->inputToken->GetTokenType() == tEnd) {
        delete this->stackTop;
        delete this->inputToken;
        inputTape.pop_front();
        this->pushdown.pop_front();

        if (inputTape.empty()) {
            throw SyntaxAnalysisSuccess();
        }
        else {
            throw InternalErrorException("Popped tEnd from input tape but there is still something left\n");
        }
    }
    else {
        throw SyntaxErrorException("Unexpected token (expected End)\n");
    }
}