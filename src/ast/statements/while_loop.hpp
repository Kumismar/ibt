/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:41
 * @ Modified time: 2024-04-08 10:24
 */

#pragma once

#include "code_block.hpp"
#include "expression.hpp"
#include "statement.hpp"

class WhileLoop : public Statement
{
private:
    Expression* condition = nullptr;
    CodeBlock* body = nullptr;

public:
    WhileLoop();
    ~WhileLoop() override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};