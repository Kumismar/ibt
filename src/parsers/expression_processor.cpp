/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 21:20
 * @ Modified time: 2024-04-29 10:36
 */

#include "expression_processor.hpp"
#include "ast.hpp"
#include "ast_node_factory.hpp"
#include "grammar_4.hpp"
#include "logger.hpp"
#include "pattern_finder.hpp"
#include "precedence_symbol.hpp"
#include "predictive_parser.hpp"
#include "syntax_error.hpp"
#include "token.hpp"

ExpressionProcessor::ExpressionProcessor(AnalysisStack& stack)
    : stack(stack)
{
}

void ExpressionProcessor::Reduce()
{
    Logger* logger = Logger::GetInstance();
    Grammar4 grammar;
    Rule tmpRule;
    PatternFinder finder;
    finder.FindFirstRule(this->stack, tmpRule);

    if (grammar.IsRule(tmpRule)) {
        logger->AddRightSide(tmpRule);

        ASTNodeFactory factory;
        Expression* tmpNode = factory.CreateASTNode(tmpRule);
        if (tmpNode != nullptr) {
            AST::GetInstance()->PushExpressionContext(tmpNode);
        }

        for (unsigned i = 0; i < tmpRule.size() + 1 /* Pop rule and '<' */; i++) {
            delete this->stack.front();
            this->stack.pop_front();
        }
        Nonterminal* toPush = new Nonterminal(nExpression);
        this->stack.push_front(toPush);


        logger->AddLeftSide(toPush);
        logger->PrintRule();

        for (Symbol* item: tmpRule) {
            delete item;
        }
    }
    else {
        for (Symbol* item: tmpRule) {
            delete item;
        }
        throw SyntaxError("Invalid token.\n");
    }
}

void ExpressionProcessor::Shift()
{
    Token* front = inputTape.front();

    this->pushPrecedence();
    this->stack.push_front(front->Clone());
    Logger::GetInstance()->AddTokenToRecents(*front);
    delete front;
    inputTape.pop_front();
}

void ExpressionProcessor::Push()
{
    Token* front = inputTape.front();
    this->stack.push_front(front->Clone());
    delete front;
    inputTape.pop_front();
}

void ExpressionProcessor::pushPrecedence()
{
    Symbol* tmpStackTop = this->stack.front();

    // Check if there is nonterminal on top of the stack, push to first or second position
    if (tmpStackTop->GetSymbolType() != Nonterminal_t) {
        this->stack.push_front(new PrecedenceSymbol(PrecedenceType::Push));
        return;
    }
    this->stack.pop_front();
    this->stack.push_front(new PrecedenceSymbol(PrecedenceType::Push));
    this->stack.push_front(tmpStackTop);
}