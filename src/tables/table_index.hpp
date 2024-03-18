/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
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