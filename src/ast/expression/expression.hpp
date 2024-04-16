/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-04-16 13:04
 */

#pragma once

#include "ast_node.hpp"
#include "nonterminal.hpp"
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
    virtual ~Expression() override = default;
    virtual void PrintTree(std::ofstream& file, int& id, int parentId) override = 0;
    virtual void ProcessToken(Token& token) override = 0;
    virtual void LinkNode(ASTNode* node, Nonterminal& nt) override = 0;
};