/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:26
 * @ Modified time: 2024-04-03 18:00
 */

#include "statement_list.hpp"

#pragma once

typedef StatementList ASTRoot;

class AST
{
private:
    ASTRoot* root = nullptr;

public:
    AST();
    ~AST();
};