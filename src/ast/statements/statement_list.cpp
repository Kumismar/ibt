/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 16:18
 * @ Modified time: 2024-04-08 12:58
 */

#pragma once

#include "statement_list.hpp"
#include "expression.hpp"
#include "internal_error.hpp"
#include "statement.hpp"

StatementList::~StatementList()
{
    if (this->statements.empty()) {
        return;
    }

    for (auto item: this->statements) {
        if (item->type == Statement_t) {
            delete item->data.statement;
        }
        else {
            delete item->data.expression;
        }
        delete item;
    }
    this->statements.clear();
}

void StatementList::ProcessToken(Token& token)
{
    return;
}

void StatementList::LinkNode(ASTNode* node, Nonterminal& nt)
{
    StatementOrExpression* tmp = new StatementOrExpression();
    if (nt.GetNonterminalType() == nExpression) {
        Expression* tmpNode = dynamic_cast<Expression*>(node);
        if (tmpNode == nullptr) {
            throw InternalError("StatementList::LinkNode (case nExpression) invalid type: " + std::string(typeid(*node).name()));
        }

        tmp->type = Expression_t;
        tmp->data.expression = tmpNode;
    }
    else {
        Statement* tmpStmt = dynamic_cast<Statement*>(node);
        if (tmpStmt == nullptr) {
            throw InternalError("StatementList::LinkNode (case nStatement) invalid type: " + std::string(typeid(*node).name()));
        }

        tmp->type = Statement_t;
        tmp->data.statement = tmpStmt;
    }
    this->statements.push_back(tmp);
}