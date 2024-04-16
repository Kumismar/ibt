/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:26
 * @ Modified time: 2024-04-16 12:43
 */


#pragma once

#include "ast_node.hpp"
#include "statement_list.hpp"
#include <fstream>
#include <stack>

class AST
{
private:
    static AST* instance;
    StatementList* root = nullptr;
    std::stack<ASTNode*> nodeContext;
    std::stack<Expression*> exprContext;
    std::ofstream* file = nullptr;
    bool printTreeFlag = false;

public:
    AST();
    ~AST();

    ASTNode* GetCurrentContext();
    Expression* GetExpressionContext();
    void PopContext();
    void PushContext(ASTNode* node);
    void PopExpressionContext();
    void PushExpressionContext(Expression* exp);
    void SetTreeFlag();
    void PrintTree();
    static AST* GetInstance();
    static void Cleanup();
};