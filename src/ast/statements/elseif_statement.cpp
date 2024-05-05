/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-16 22:23
 */

#include "elseif_statement.hpp"
#include "expression.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "statement_list.hpp"

ElseifStatement::ElseifStatement()
{
    this->nodeType = Statement_n;
}

ElseifStatement::~ElseifStatement()
{
    delete this->condition;
    delete this->body;
}

void ElseifStatement::PrintTree(std::ofstream& file, int& id, int parentId)
{
    int currentId = id++;
    file << "node" << parentId << " -> node" << currentId << ";\n";
    file << "node" << currentId << " [label=\"ElseIfStatement\"];\n";

    this->condition->PrintTree(file, id, currentId);
    this->body->PrintTree(file, id, currentId);
}
void ElseifStatement::LinkNode(ASTNode* node, Nonterminal& nt)
{
    switch (nt.GetNonterminalType()) {
        case nExpression: {
            auto* tmp = dynamic_cast<Expression*>(node);
            if (tmp == nullptr) {
                throw InternalError("ElseifStatement::LinkNode (case nExpression) invalid type: " + std::string(typeid(*node).name()));
            }

            this->condition = tmp;
            break;
        }
        case nCodeBlock: {
            auto* tmp = dynamic_cast<StatementList*>(node);
            if (tmp == nullptr) {
                throw InternalError("ElseifStatement::LinkNode (case nCodeBlock) invalid type: " + std::string(typeid(*node).name()));
            }

            this->body = tmp;
            break;
        }
        default: {
            return;
        }
    }
}
