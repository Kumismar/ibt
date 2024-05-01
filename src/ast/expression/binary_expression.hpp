/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:22
 * @ Modified time: 2024-05-01 12:20
 */

#pragma once

#include "expression.hpp"
#include "operator.hpp"
#include "token.hpp"

class BinaryExpression : public Expression
{
private:
    Expression* left = nullptr;
    Operator* optr = nullptr;
    Expression* right = nullptr;

public:
    BinaryExpression(TokenType t);
    ~BinaryExpression() override;

    Expression* GetLeft() const;
    Expression* GetRight() const;

    void PrintTree(std::ofstream& file, int& id, int parentId) override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};