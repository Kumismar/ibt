/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-15 15:02
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
    while (!this->nodeContext.empty()) {
        // All the objects in AST were already deleted, just pop the pointers
        AST::instance->nodeContext.pop();
    }
    if (this->root != nullptr) {
        delete this->root;
        this->root = nullptr;
    }
}

ASTNode* AST::GetCurrentContext()
{
    if (this->nodeContext.empty()) {
        return nullptr;
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
    AST::instance = nullptr;
}
