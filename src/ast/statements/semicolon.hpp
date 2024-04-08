/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:47
 * @ Modified time: 2024-04-08 11:14
 */

#pragma once

#include "statement.hpp"

class Semicolon : public Statement
{
public:
    ~Semicolon() override = default;
    void ProcessToken(Token& token) override
    {
    }
    void LinkNode(ASTNode* node, Nonterminal& nt) override
    {
    }
};