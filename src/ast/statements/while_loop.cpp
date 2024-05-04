/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-17 16:13
 */

#include "while_loop.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "statement.hpp"

WhileLoop::WhileLoop()
{
    this->type = While_s;
}

WhileLoop::~WhileLoop()
{
    delete this->body;
    delete this->condition;
}

void WhileLoop::PrintTree(std::ofstream& file, int& id, int parentId)
{
    int currentId = id++;
    file << "node" << parentId << " -> node" << currentId << ";\n";
    file << "node" << currentId << " [label=\"WhileLoop\"];\n";

    if (this->condition != nullptr) {
        this->condition->PrintTree(file, id, currentId);
    }

    if (this->body != nullptr) {
        this->body->PrintTree(file, id, currentId);
    }
}

void WhileLoop::ProcessToken(Token& token)
{
    }

void WhileLoop::LinkNode(ASTNode* node, Nonterminal& nt)
{
    switch (nt.GetNonterminalType()) {
        case nExpression: {
            auto* tmp = dynamic_cast<Expression*>(node);
            if (tmp == nullptr) {
                throw InternalError("WhileLoop::LinkNode (case nExpression) invalid type: " + std::string(typeid(*node).name()));
            }

            this->condition = tmp;
            break;
        }
        case nCodeBlock: {
            auto* tmp = dynamic_cast<StatementList*>(node);
            if (tmp == nullptr) {
                throw InternalError("WhileLoop::LinkNode (case nCodeBlock) invalid type: " + std::string(typeid(*node).name()));
            }

            this->body = tmp;
            break;
        }
        default: {
            return;
        }
    }
}
