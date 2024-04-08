/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-08 12:29
 */

#include "ast.hpp"
#include "internal_error.hpp"
#include "statement_list.hpp"

AST* AST::instance = nullptr;

AST::AST()
{
    this->root = new StatementList();
    this->nodeContext.push(this->root);
}

AST::~AST()
{
    delete this->root;
    while (!this->nodeContext.empty()) {
        // All the objects in AST were already deleted, just pop the pointers
        AST::instance->nodeContext.pop();
    }
}

ASTNode* AST::GetCurrentContext()
{
    if (this->nodeContext.empty()) {
        throw InternalError("AST::GetCurrentContext node context empty\n");
    }
    return this->nodeContext.top();
}

void AST::PopContext()
{
    this->nodeContext.pop();
}

void AST::PushContext(ASTNode* node)
{
    this->nodeContext.push(node);
}

AST* AST::GetInstance()
{
    if (AST::instance == nullptr) {
        AST::instance = new AST();
    }
    return AST::instance;
}

void AST::Cleanup()
{
    if (AST::instance == nullptr) {
        return;
    }
    delete AST::instance;
}
