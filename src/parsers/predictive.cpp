/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-22 22:14
 * @ Modified time: 2024-04-07 20:42
 */

#include "predictive.hpp"
#include "analysis_success.hpp"
#include "ast.hpp"
#include "ast_node.hpp"
#include "ast_node_factory.hpp"
#include "exception_base.hpp"
#include "function_parsed.hpp"
#include "grammar_factory.hpp"
#include "internal_error.hpp"
#include "ll_table.hpp"
#include "logger.hpp"
#include "nonterminal.hpp"
#include "precedence.hpp"
#include "stack_item.hpp"
#include "syntax_error.hpp"
#include "table_index.hpp"
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

void PredictiveParser::Parse(bool parseFunction)
{
    if (parseFunction) {
        this->parsingFunction = true;
        this->firstFuncName = true;
    }

    while (true) {
        this->stackTop = this->pushdown.front();
        if (inputTape.empty()) {
            throw SyntaxError("Missing token(s).\n");
        }
        this->inputToken = inputTape.front();

        if (*this->inputToken == tFuncEnd) {
            delete this->inputToken;
            inputTape.pop_front();
            inputTape.push_front(new Token(tFuncConst));
            throw FunctionParsed();
        }

        switch (this->stackTop->GetSymbolType()) {
            case Nonterminal_t: {
                this->parseNonterminal();
                break;
            }
            case Token_t: {
                this->parseToken();
                break;
            }
            default:
                throw InternalError("Unexpected item type: " + std::string(typeid(*this->stackTop).name()) + "\n");
        }
    }
}

bool PredictiveParser::returnedEpsilon(Rule& expandedRule)
{
    Symbol* front = expandedRule.front();
    if (expandedRule.size() == 1 && front->GetSymbolType() == Token_t) {
        Token* t = dynamic_cast<Token*>(front);
        if (t == nullptr) {
            throw InternalError("Dynamic cast to Token* failed, real type: " + std::string(typeid(front).name()) + "\n");
        }
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
        throw InternalError("Dynamic cast to Nonterminal* failed, real type:" + std::string(typeid(*this->stackTop).name()) + "\n");
    }

    if (stackNT->GetNonterminalType() == nStop) {
        AST::GetInstance()->PopContext();
        delete this->stackTop;
        return;
    }
    // Expression => give control to precedence parser
    else if (stackNT->GetNonterminalType() == nExpression) {
        // If not parsing function call, give control to precedence parser
        if (!(*this->inputToken == tFuncName && this->parsingFunction) ||
            // If parsing function call but new funcName is found, parse the new function call
            (*this->inputToken == tFuncName && !this->firstFuncName)) {
            PrecedenceParser* precedenceParser = new PrecedenceParser(this->pushdown);
            try {
                precedenceParser->Parse();
                delete precedenceParser;
            }
            catch (ExceptionBase const& e) {
                delete precedenceParser;
                throw;
            }
            return;
        }
    }

    LLTableIndex tableItem = (*this->table)[*stackNT][*this->inputToken];
    // Rule exists -> pop old nonterminal, expand it and push new string to the stack
    if (tableItem != LLTableIndex({ 0, 0 })) {
        ASTNode* node = ASTNodeFactory::CreateASTNode(*stackNT, *this->inputToken);
        // if nonterminal doesnt have corresponding AST node, nullptr is returned
        if (node != nullptr) {
            AST::GetInstance()->GetCurrentContext()->LinkNode(node, *stackNT);
        }

        Logger* logger = Logger::GetInstance();
        logger->AddLeftSide(this->stackTop);

        if (!(this->parsingFunction && *stackNT == nExpression)) {
            delete this->pushdown.front();
            this->pushdown.pop_front();
        }

        Grammar* grammar = GrammarFactory::CreateGrammar(tableItem.grammarNumber);
        Rule expandedRule = grammar->Expand(tableItem.ruleNumber);
        logger->AddRightSide(expandedRule);

        // if right side is not epsilon, it will be pushed
        if (!this->returnedEpsilon(expandedRule)) {
            for (Symbol* item: expandedRule) {
                this->pushdown.push_front(item->Clone());
            }
        }

        logger->PrintRule();
        delete grammar;
    }
    else {
        throw SyntaxError("Invalid token.\n");
    }
}

void PredictiveParser::parseToken()
{
    Token* stackToken = dynamic_cast<Token*>(this->stackTop);
    if (stackToken == nullptr) {
        throw InternalError("Dynamic cast to Token* failed, real type:" + std::string(typeid(*this->stackTop).name()) + "\n");
    }

    // Case $:
    if (stackToken->GetTokenType() == tEnd) {
        this->parseEnd();
    }

    // Case T:
    if (*stackToken == *this->inputToken) {
        if (*stackToken == tFuncName) {
            this->firstFuncName = false;
        }
        // AST nodes gradually add information to themselves based on tokens parsed
        AST::GetInstance()->GetCurrentContext()->ProcessToken(*this->inputToken);
        Logger::GetInstance()->AddTokenToRecents(*this->inputToken);
        delete this->inputToken;
        delete this->pushdown.front();
        this->pushdown.pop_front();
        inputTape.pop_front();
        return;
    }
    else {
        throw SyntaxError("Unexpected token, expected: " + stackToken->GetTypeString() + "\n");
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
            throw InternalError("Popped tEnd from input tape but there is still something left\n");
        }
    }
    else {
        throw SyntaxError("Invalid token.\n");
    }
}