/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-04 11:00
 * @ Modified time: 2024-04-04 11:16
 */

#pragma once

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
};