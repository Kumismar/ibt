/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-07 22:56
 */

#include "return_statement.hpp"
#include "expression.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "statement.hpp"

ReturnStatement::ReturnStatement()
{
    this->type = Return_s;
}

void ReturnStatement::ProcessToken(Token& token)
{
    return;
}

void ReturnStatement::LinkNode(ASTNode* node, Nonterminal& nt)
{
    if (nt.GetNonterminalType() == nExpression) {
        Expression* tmp = dynamic_cast<Expression*>(node);
        if (tmp == nullptr) {
            throw InternalError("ReturnStatement::LinkNode (case nExpression) invalid type: " + std::string(typeid(*node).name()));
        }

        this->expr = tmp;
    }
}
