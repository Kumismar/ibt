/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:16
 * @ Modified time: 2024-04-07 16:47
 */

#pragma once

#include "elseif_statement.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include "statement_list.hpp"
#include <vector>

class IfStatement : public Statement
{
private:
    Expression* condition = nullptr;
    StatementList* ifBody = nullptr;
    std::vector<ElseifStatement*> elseifs;
    StatementList* elseBody = nullptr;

public:
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};