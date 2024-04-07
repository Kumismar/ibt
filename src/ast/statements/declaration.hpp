/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:44
 * @ Modified time: 2024-04-07 16:47
 */

#pragma once

#include "ast_node.hpp"
#include "expression.hpp"
#include "operand.hpp"
#include "statement.hpp"

class Declaration : public Statement
{
private:
    Operand* left = nullptr;
    Expression* right = nullptr;

public:
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};