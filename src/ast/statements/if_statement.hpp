/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:16
 * @ Modified time: 2024-04-08 10:28
 */

#pragma once

#include "code_block.hpp"
#include "elseif_statement.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include <vector>

class IfStatement : public Statement
{
private:
    bool processingElse = false;
    Expression* condition = nullptr;
    CodeBlock* ifBody = nullptr;
    std::vector<ElseifStatement*> elseifs;
    CodeBlock* elseBody = nullptr;

public:
    IfStatement();
    ~IfStatement() override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};