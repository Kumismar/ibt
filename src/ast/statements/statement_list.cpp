/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 16:18
 * @ Modified time: 2024-04-07 16:24
 */

#pragma once

#include "statement_list.hpp"

void StatementList::Cleanup()
{
    if (this->statements.empty()) {
        return;
    }

    for (auto item: this->statements) {
        if (item->type == Statement_t) {
            delete item->data.statement;
        }
        else {
            delete item->data.expression;
        }
    }
}