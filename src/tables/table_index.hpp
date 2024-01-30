#pragma once

typedef struct llTableIndex {
    unsigned grammarNumber;
    unsigned ruleNumber;

    bool operator!=(const struct llTableIndex& other) const
    {
        return ((this->grammarNumber == other.grammarNumber) && (this->ruleNumber == other.ruleNumber));
    }
} LLTableIndex;