/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-16 14:21
 */

#include "if_statement.hpp"
#include "code_block.hpp"
#include "elseif_statement.hpp"
#include "expression.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "token.hpp"

IfStatement::IfStatement()
{
    this->type = If_s;
}

IfStatement::~IfStatement()
{
    if (this->condition != nullptr) {
        delete this->condition;
    }

    if (this->elseBody != nullptr) {
        delete this->elseBody;
    }

    if (this->ifBody != nullptr) {
        delete this->ifBody;
    }

    if (!this->elseifs.empty()) {
        for (auto elseif: this->elseifs) {
            delete elseif;
        }
        this->elseifs.clear();
    }
}

void IfStatement::PrintTree(std::ofstream& file, int& id, int parentId)
{
    int currentId = id++;
    file << "node" << parentId << " -> node" << currentId << ";\n";
    file << "node" << currentId << " [label=\"IfStatement\"];\n";

    this->condition->PrintTree(file, id, currentId);
    this->ifBody->PrintTree(file, id, currentId);

    if (!this->elseifs.empty()) {
        for (auto elseif: this->elseifs) {
            elseif->PrintTree(file, id, currentId);
        }
    }

    if (this->elseBody != nullptr) {
        this->elseBody->PrintTree(file, id, currentId);
    }
}

void IfStatement::ProcessToken(Token& token)
{
    if (token == tElse) {
        this->processingElse = true;
    }
}

void IfStatement::LinkNode(ASTNode* node, Nonterminal& nt)
{
    switch (nt.GetNonterminalType()) {
        case nCodeBlock: {
            CodeBlock* tmp = dynamic_cast<CodeBlock*>(node);
            if (tmp == nullptr) {
                throw InternalError("IfStatement::LinkNode (case nCodeBlock) invalid type: " + std::string(typeid(*node).name()));
            }

            if (this->processingElse) {
                this->elseBody = tmp;
            }
            else {
                this->ifBody = tmp;
            }
            break;
        }
        case nIf2: {
            ElseifStatement* tmp = dynamic_cast<ElseifStatement*>(node);
            if (tmp == nullptr) {
                throw InternalError("IfStatement::LinkNode (case nIf2) invalid type: " + std::string(typeid(*node).name()));
            }

            this->elseifs.push_back(tmp);
            break;
        }
        case nExpression: {
            Expression* tmp = dynamic_cast<Expression*>(node);
            if (tmp == nullptr) {
                throw InternalError("IfStatement::LinkNode (case nExpression) invalid type: " + std::string(typeid(*node).name()));
            }

            this->condition = tmp;
            break;
        }
        default: {
            return;
        }
    }
}
