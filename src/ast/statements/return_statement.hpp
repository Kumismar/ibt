/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:46
 * @ Modified time: 2024-04-03 17:59
 */

#pragma once

#include "expression.hpp"
#include "statement.hpp"

class ReturnStatement : public Statement
{
private:
    Expression* expr = nullptr;
};