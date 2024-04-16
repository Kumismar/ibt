/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 18:14
 * @ Modified time: 2024-04-16 13:56
 */

#pragma once

#include "operand.hpp"
#include "token.hpp"

class Constant : public Operand
{
public:
    Constant(Token& t);
    Constant(TokenType t);
    ~Constant() override;
    void PrintTree(std::ofstream& file, int& id, int parentId) override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};