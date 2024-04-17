/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:19
 * @ Modified time: 2024-04-16 22:23
 */

#pragma once

#include "expression.hpp"
#include "statement.hpp"
#include "statement_list.hpp"

class ElseifStatement : public Statement
{
private:
    Expression* condition = nullptr;
    StatementList* body = nullptr;

public:
    ElseifStatement();
    ~ElseifStatement() override;
    void PrintTree(std::ofstream& file, int& id, int parentId) override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};