/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:26
 * @ Modified time: 2024-04-16 13:05
 */

#pragma once

#include "expression.hpp"
#include "operand.hpp"
#include "operator.hpp"

class UnaryExpression : public Expression
{
private:
    Operator* optr = nullptr;
    Expression* operand = nullptr;

public:
    UnaryExpression(TokenType t);
    ~UnaryExpression() override;
    void PrintTree(std::ofstream& file, int& id, int parentId) override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};