/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-04 11:00
 * @ Modified time: 2024-04-17 08:46
 */

#pragma once

#include "nonterminal.hpp"
#include "token.hpp"
#include <fstream>
typedef enum nodeType
{
    Expression_n,
    Statement_n,
    StatementList_n,
    FuncDef_n
} NodeType;

class ASTNode
{
protected:
    NodeType nodeType;

public:
    virtual ~ASTNode() = default;
    virtual void PrintTree(std::ofstream& file, int& id, int parentId) = 0;
    virtual void ProcessToken(Token& token) = 0;
    virtual void LinkNode(ASTNode* node, Nonterminal& nt) = 0;

    NodeType GetNodeType() const
    {
        return nodeType;
    }
};