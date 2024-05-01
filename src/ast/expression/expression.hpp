/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-05-01 12:40
 */

#pragma once

#include "ast_node.hpp"
#include "nonterminal.hpp"
typedef enum expressionType
{
    Unary,
    Binary,
} ExpressionType;

class Expression : public ASTNode
{
protected:
    ExpressionType expressionType;

public:
    virtual ~Expression() override = default;
    virtual void PrintTree(std::ofstream& file, int& id, int parentId) override = 0;
    virtual void ProcessToken(Token& token) override = 0;
    virtual void LinkNode(ASTNode* node, Nonterminal& nt) override = 0;
};