/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-04 11:00
 * @ Modified time: 2024-04-08 11:01
 */

#pragma once

#include "nonterminal.hpp"
#include "token.hpp"
typedef enum nodeType
{
    Expression_n,
    Statement_n,
    StatementList_n
} NodeType;

class ASTNode
{
protected:
    NodeType type;

public:
    virtual ~ASTNode() = default;
    virtual void ProcessToken(Token& token) = 0;
    virtual void LinkNode(ASTNode* node, Nonterminal& nt) = 0;
};