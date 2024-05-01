/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:44
 * @ Modified time: 2024-05-01 12:34
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
    Declaration();
    ~Declaration() override;

    Operand* GetLeft() const;
    Expression* GetRight() const;

    void PrintTree(std::ofstream& file, int& id, int parentId) override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};