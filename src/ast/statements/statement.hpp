/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-05-03 11:20
 */

#pragma once

#include "ast_node.hpp"
#include "nonterminal.hpp"

typedef enum statementType
{
    FuncDef_s,
    Declaration_s,
    Return_s,
    If_s,
    Elseif_s,
    While_s,
    For_s,
    Semicolon_s,
    Expression_s,
    CodeBlock_s
} StatementType;

class Statement : public ASTNode
{
protected:
    StatementType type;

public:
    virtual ~Statement() override = default;
    virtual void ProcessToken(Token& t) override = 0;
    virtual void LinkNode(ASTNode* node, Nonterminal& nt) override = 0;
};