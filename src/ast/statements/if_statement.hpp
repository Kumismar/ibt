/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:16
 * @ Modified time: 2024-04-17 16:12
 */

#pragma once

#include "elseif_statement.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include <vector>

class IfStatement : public Statement
{
private:
    bool processingElse = false;
    Expression* condition = nullptr;
    StatementList* ifBody = nullptr;
    std::vector<ElseifStatement*> elseifs;
    StatementList* elseBody = nullptr;

public:
    IfStatement();
    ~IfStatement() override;
    void PrintTree(std::ofstream& file, int& id, int parentId) override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};