#pragma once

typedef struct tableIndex {
    unsigned grammarNumber;
    unsigned ruleNumber;

    bool operator!=(const struct tableIndex& other) const
    {
        return ((this->grammarNumber == other.grammarNumber) && (this->ruleNumber == other.ruleNumber));
    }
} TableIndex;