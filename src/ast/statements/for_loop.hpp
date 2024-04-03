/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:41
 * @ Modified time: 2024-04-03 17:57
 */

#pragma once

#include "declOrExp.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include "statement_list.hpp"

class ForLoop : public Statement
{
private:
    DeclOrExp* init = nullptr;
    Expression* condition = nullptr;
    Expression* endExpr = nullptr;
    StatementList* body = nullptr;
};