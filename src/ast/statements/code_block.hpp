/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 16:36
 * @ Modified time: 2024-04-07 16:47
 */

#pragma once

#include "statement.hpp"
#include "statement_list.hpp"
class CodeBlock : public Statement
{
private:
    StatementList* statements;

public:
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};