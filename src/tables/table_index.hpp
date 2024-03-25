/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-23 17:37
 */

#pragma once

typedef struct llTableIndex {
    unsigned grammarNumber;
    unsigned ruleNumber;

    bool operator!=(const struct llTableIndex& other) const
    {
        return ((this->grammarNumber != other.grammarNumber) || (this->ruleNumber != other.ruleNumber));
    }
} LLTableIndex;