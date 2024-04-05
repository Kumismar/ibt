/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:26
 * @ Modified time: 2024-04-04 11:04
 */


#pragma once

#include "ast_node.hpp"

class AST
{
private:
    ASTNode* root = nullptr;

public:
    AST();
    ~AST();
};