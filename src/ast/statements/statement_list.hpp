/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-04-07 20:48
 */

#pragma once

#include "expression.hpp"
#include "statement.hpp"
#include <vector>

typedef enum type
{
    Statement_t,
    Expression_t
} StOrExpType;

typedef union statementData
{
    Statement* statement;
    Expression* expression;
} StOrExpData;

typedef struct statementOrExpression {
    StOrExpType type;
    StOrExpData data;
} StatementOrExpression;

class StatementList : public ASTNode
{
private:
    std::vector<StatementOrExpression*> statements;

public:
    void Cleanup();
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};