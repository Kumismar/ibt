/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-08 12:44
 */

#include "for_loop.hpp"
#include "code_block.hpp"
#include "expression.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "statement.hpp"
#include "token.hpp"

ForLoop::ForLoop()
{
    this->type = For_s;
    this->init = new Initialization();
    this->init->type = NoType;
}

ForLoop::~ForLoop()
{
    if (this->init->type == Decl) {
        delete this->init->data.decl;
    }
    else if (this->init->type == Expr) {
        delete this->init->data.expr;
    }
    delete this->init;

    if (this->condition != nullptr) {
        delete this->condition;
    }

    if (this->endExpr != nullptr) {
        delete this->endExpr;
    }

    if (this->body != nullptr) {
        delete this->body;
    }
}

void ForLoop::ProcessToken(Token& token)
{
    return;
}

void ForLoop::LinkNode(ASTNode* node, Nonterminal& nt)
{
    switch (nt.GetNonterminalType()) {
        case nCodeBlock: {
            CodeBlock* tmp = dynamic_cast<CodeBlock*>(node);
            if (tmp == nullptr) {
                throw InternalError("ForLoop::LinkNode (case nCodeBlock) invalid type: " + std::string(typeid(*node).name()));
            }

            this->body = tmp;
            break;
        }
        case nExpression: {
            Expression* tmp = dynamic_cast<Expression*>(node);
            if (tmp == nullptr) {
                throw InternalError("ForLoop::LinkNode (case nStatement) invalid type: " + std::string(typeid(*node).name()));
            }

            if (this->phase == INITIALIZATION) {
                this->init->type = Expr;
                this->init->data.expr = tmp;
                this->phase = CONDITION;
            }
            else if (this->phase == CONDITION) {
                this->condition = tmp;
                this->phase = END_EXPRESSION;
            }
            else if (this->phase == END_EXPRESSION) {
                this->endExpr = tmp;
                this->phase = BODY;
            }
            break;
        }
        case nDeclOrExpr: {
            if (!this->nextIsType()) {
                return;
            }

            Declaration* tmp = dynamic_cast<Declaration*>(node);
            if (tmp == nullptr) {
                throw InternalError("ForLoop::LinkNode (case nDeclOrExp) invalid type: " + std::string(typeid(*node).name()));
            }

            this->init->type = Decl;
            this->init->data.decl = tmp;
            break;
        }
        default: {
            return;
        }
    }
}

bool ForLoop::nextIsType()
{
    Token* next = inputTape.front();
    return (*next == tInt || *next == tFloat || *next == tBool || *next == tString);
}
