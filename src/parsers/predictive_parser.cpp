/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-22 22:14
 * @ Modified time: 2024-05-02 20:05
 */

#include "predictive_parser.hpp"
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
#include "precedence_parser.hpp"
#include "stack_item.hpp"
#include "symbol_handler.hpp"
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
        this->handleSpecialCases();

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
    AST* ast = AST::GetInstance();
    Nonterminal* stackNT = dynamic_cast<Nonterminal*>(this->stackTop->Clone());
    if (stackNT == nullptr) {
        throw InternalError("Dynamic cast to Nonterminal* failed, real type:" + std::string(typeid(*this->stackTop).name()) + "\n");
    }

    // nStop => end of ASTNode context
    if (stackNT->GetNonterminalType() == nStop) {
        ast->PopContext();
        delete this->stackTop;
        this->pushdown.pop_front();
        delete stackNT;
        return;
    }
    // Expression => give control to precedence parser
    else if (stackNT->GetNonterminalType() == nExpression) {
        bool notParsingFunctionCall = !(*this->inputToken == tFuncName && this->parsingFunction);
        // Function call nested within another function call.
        bool newFuncNameFound = *this->inputToken == tFuncName && !this->firstFuncName;

        if (notParsingFunctionCall || newFuncNameFound) {
            this->parseExpression(stackNT);
            delete stackNT;
            return;
        }
    }

    LLTableIndex tableItem = (*this->table)[*stackNT][*this->inputToken];
    // Rule exists -> pop old nonterminal, expand it and push new string to the stack
    if (tableItem != LLTableIndex({ 0, 0 })) {
        SymbolHandler handler(this->pushdown);
        handler.Expand(this->parsingFunction, tableItem);
    }
    else {
        delete stackNT;
        throw SyntaxError("Invalid token.\n");
    }
    delete stackNT;
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
        if (*this->inputToken == tFuncName) {
            this->firstFuncName = false;
        }
        SymbolHandler handler(this->pushdown);
        handler.Pop();
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
            // Not empty inputTape should never happen in this case, syntax error would be thrown earlier, which is why InternalError.
            throw InternalError("Popped tEnd from input tape but there is still something left\n");
        }
    }
    else {
        throw SyntaxError("Invalid token.\n");
    }
}

void PredictiveParser::parseExpression(Nonterminal* stackNT)
{
    AST* ast = AST::GetInstance();
    PrecedenceParser precedenceParser(this->pushdown);
    try {
        precedenceParser.Parse();
        // After precedence parsing, link the expression to the current node.
        ASTNode* context = ast->GetCurrentContext();
        if (context != nullptr) { // nullptr only in case of unit tests
            context->LinkNode(ast->GetExpressionContext(), *stackNT);
            ast->PopExpressionContext();
        }
    }
    catch (ExceptionBase const& e) {
        delete stackNT;
        throw;
    }
    return;
}

void PredictiveParser::handleSpecialCases()
{
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
}