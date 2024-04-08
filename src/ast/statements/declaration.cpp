/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-08 12:02
 */

#include "declaration.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "statement.hpp"
#include "token.hpp"
#include "variable.hpp"

Declaration::Declaration()
{
    this->type = Declaration_s;
}

Declaration::~Declaration()
{
    if (this->left != nullptr) {
        delete this->left;
    }

    if (this->right != nullptr) {
        delete this->right;
    }
}

void Declaration::ProcessToken(Token& token)
{
    if (token == tVariable) {
        this->left = new Variable(token);
    }
}

void Declaration::LinkNode(ASTNode* node, Nonterminal& nt)
{
    switch (nt.GetNonterminalType()) {
        case nExpression: {
            Expression* tmp = dynamic_cast<Expression*>(node);
            if (tmp == nullptr) {
                throw InternalError("Declaration::LinkNode (case nExpression) invalid type: " + std::string(typeid(*node).name()));
            }

            this->right = tmp;
            break;
        }
        default: {
            return;
        }
    }
}
