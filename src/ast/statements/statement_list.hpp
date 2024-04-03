/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-04-03 17:52
 */

#pragma once

#include "statement.hpp"
#include <vector>

class StatementList
{
private:
    std::vector<Statement*> statements;
};