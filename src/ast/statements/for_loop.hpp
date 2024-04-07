/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:41
 * @ Modified time: 2024-04-07 22:57
 */

#pragma once

#include "code_block.hpp"
#include "decl_or_exp.hpp"
#include "expression.hpp"
#include "statement.hpp"

typedef enum phase
{
    INITIALIZATION,
    CONDITION,
    END_EXPRESSION,
    BODY
} Phase;

class ForLoop : public Statement
{
private:
    Phase phase = INITIALIZATION;
    DeclOrExp init;
    Expression* condition = nullptr;
    Expression* endExpr = nullptr;
    CodeBlock* body = nullptr;

    bool nextIsType();

public:
    ForLoop();
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};