/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:41
 * @ Modified time: 2024-04-17 16:12
 */

#pragma once

#include "expression.hpp"
#include "statement.hpp"
#include "statement_list.hpp"

class WhileLoop : public Statement
{
private:
    Expression* condition = nullptr;
    StatementList* body = nullptr;

public:
    WhileLoop();
    ~WhileLoop() override;
    void PrintTree(std::ofstream& file, int& id, int parentId) override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};