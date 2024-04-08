/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:41
 * @ Modified time: 2024-04-08 12:43
 */

#pragma once

#include "code_block.hpp"
#include "declaration.hpp"
#include "expression.hpp"
#include "statement.hpp"

typedef enum phase
{
    INITIALIZATION,
    CONDITION,
    END_EXPRESSION,
    BODY
} Phase;

typedef enum initType
{
    Decl,
    Expr,
    NoType
} InitType;

typedef union initData
{
    Declaration* decl;
    Expression* expr;
} InitData;

typedef struct init {
    InitType type;
    InitData data;
} Initialization;

class ForLoop : public Statement
{
private:
    Phase phase = INITIALIZATION;
    Initialization* init = nullptr;
    Expression* condition = nullptr;
    Expression* endExpr = nullptr;
    CodeBlock* body = nullptr;

    bool nextIsType();

public:
    ForLoop();
    ~ForLoop() override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};