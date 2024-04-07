/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-07 17:00
 */

#include "ast.hpp"
#include "internal_error.hpp"
#include "statement_list.hpp"

AST::AST()
{
    this->root = new StatementList();
    this->nodeContext.push(this->root);
}

ASTNode* AST::GetCurrentContext()
{
    if (this->nodeContext.empty()) {
        throw InternalError("");
    }
    return this->nodeContext.top();
}

void AST::PopContext()
{
    this->nodeContext.pop();
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
    AST::instance->root->Cleanup();
    while (!AST::instance->nodeContext.empty()) {
        // All the objects in AST were already deleted, just pop the pointers
        AST::instance->nodeContext.pop();
    }
}
