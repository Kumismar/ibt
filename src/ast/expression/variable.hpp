/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 18:21
 * @ Modified time: 2024-04-16 13:49
 */

#pragma once

#include "operand.hpp"
#include "token.hpp"

class Variable : public Operand
{
private:
    std::string name;

public:
    Variable(Token& token);
    ~Variable() override = default;
    void PrintTree(std::ofstream& file, int& id, int parentId) override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};