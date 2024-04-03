/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:19
 * @ Modified time: 2024-04-03 17:57
 */

#pragma once

#include "expression.hpp"
#include "statement.hpp"
#include "statement_list.hpp"

class ElseifStatement : public Statement
{
private:
    Expression* condition = nullptr;
    StatementList* body = nullptr;
};