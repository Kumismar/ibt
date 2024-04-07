/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:26
 * @ Modified time: 2024-04-07 16:59
 */


#pragma once

#include "ast_node.hpp"
#include "statement_list.hpp"
#include <stack>

class AST
{
private:
    static AST* instance;
    StatementList* root = nullptr;
    std::stack<ASTNode*> nodeContext;

public:
    AST();
    ~AST();

    ASTNode* GetCurrentContext();
    void PopContext();
    static AST* GetInstance();
    static void Cleanup();
};