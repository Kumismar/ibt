/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 20:43
 * @ Modified time: 2024-04-07 23:03
 */

#include "code_block.hpp"
#include "internal_error.hpp"

CodeBlock::CodeBlock()
{
    this->type = CodeBlock_s;
}

void CodeBlock::ProcessToken(Token& token)
{
    return;
}

void CodeBlock::LinkNode(ASTNode* node, Nonterminal& nt)
{
    switch (nt.GetNonterminalType()) {
        case nStatement: {
            Statement* tmp = dynamic_cast<Statement*>(node);
            if (tmp == nullptr) {
                throw InternalError("CodeBlock::LinkNode (case nStatement) invalid type: " + std::string(typeid(*node).name()));
            }

            this->stType = Single_t;
            this->statements.statement = tmp;
        }
        case nStatementList: {
            StatementList* tmp = dynamic_cast<StatementList*>(node);
            if (tmp == nullptr) {
                throw InternalError("CodeBlock::LinkNode (case nStatementList) invalid type: " + std::string(typeid(*node).name()));
            }

            this->stType = List_t;
            this->statements.list = tmp;
        }
        default: {
            return;
        }
    }
}
