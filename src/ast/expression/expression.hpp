/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-04-07 16:25
 */

#pragma once

#include "ast_node.hpp"
typedef enum expressionType
{
    Unary,
    Binary,
    SingleOperand
} ExpressionType;

class Expression : public ASTNode
{
protected:
    ExpressionType type;

public:
    virtual ~Expression();
    void ProcessToken(Token& token) override;
};