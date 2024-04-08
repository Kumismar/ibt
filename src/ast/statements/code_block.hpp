/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 16:36
 * @ Modified time: 2024-04-08 12:03
 */

#pragma once

#include "statement.hpp"
#include "statement_list.hpp"

typedef enum stType
{
    Single_t,
    List_t,
    NoStatement
} StType;

typedef union stOrStList
{
    StatementList* list;
    Statement* statement;
} StOrStList;

class CodeBlock : public Statement
{
private:
    StType stType;
    StOrStList statements;

public:
    CodeBlock();
    ~CodeBlock() override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};