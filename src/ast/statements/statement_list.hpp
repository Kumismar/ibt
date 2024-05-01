/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-05-01 12:55
 */

#pragma once

#include "expression.hpp"
#include "statement.hpp"
#include <fstream>
#include <vector>

typedef enum type
{
    Statement_t,
    Expression_t,
    StList_t
} StOrExpType;

// Forward declaration for circular dependency
class StatementList;

typedef union statementData
{
    Statement* statement;
    Expression* expression;
    StatementList* statementList;
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
    StatementList();
    ~StatementList() override;
    std::vector<StatementOrExpression*> GetStatements() const;
    void PrintTree(std::ofstream& file, int& id, int parentId) override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};