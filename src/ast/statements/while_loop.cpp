/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-16 14:17
 */

#include "while_loop.hpp"
#include "code_block.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "statement.hpp"

WhileLoop::WhileLoop()
{
    this->type = While_s;
}

WhileLoop::~WhileLoop()
{
    if (this->body != nullptr) {
        delete this->body;
    }

    if (this->condition != nullptr) {
        delete this->condition;
    }
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
    return;
}

void WhileLoop::LinkNode(ASTNode* node, Nonterminal& nt)
{
    switch (nt.GetNonterminalType()) {
        case nExpression: {
            Expression* tmp = dynamic_cast<Expression*>(node);
            if (tmp == nullptr) {
                throw InternalError("WhileLoop::LinkNode (case nExpression) invalid type: " + std::string(typeid(*node).name()));
            }

            this->condition = tmp;
            break;
        }
        case nCodeBlock: {
            CodeBlock* tmp = dynamic_cast<CodeBlock*>(node);
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
