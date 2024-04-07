/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:41
 * @ Modified time: 2024-04-07 16:47
 */

#pragma once

#include "decl_or_exp.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include "statement_list.hpp"

class ForLoop : public Statement
{
private:
    DeclOrExp* init = nullptr;
    Expression* condition = nullptr;
    Expression* endExpr = nullptr;
    StatementList* body = nullptr;

public:
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};