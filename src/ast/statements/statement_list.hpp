/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-04-04 11:17
 */

#pragma once

#include "expression.hpp"
#include "statement.hpp"
#include <vector>

typedef union statementOrExpression
{
    Statement* statement;
    Expression* expression;
} StatementOrExpression;

class StatementList
{
private:
    std::vector<StatementOrExpression*> statements;
};