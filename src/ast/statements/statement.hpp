/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-04-07 16:24
 */

#pragma once

#include "ast_node.hpp"

typedef enum statementType
{
    Assignment_s,
    Definition_s,
    Return_s,
    If_s,
    While_s,
    For_s,
    Semicolon_s,
    Expression_s
} StatementType;

class Statement : public ASTNode
{
protected:
    StatementType type;

public:
    virtual ~Statement();
};