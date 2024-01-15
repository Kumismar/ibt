#pragma once

#include "grammar.hpp"
#include "nonterminal.hpp"
#include "nonterminal_type.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include "token_type.hpp"
#include <list>
#include <vector>

class Grammar4 : public Grammar
{
private:
    const std::vector<std::list<StackItem>>& rightSideRules = {
        {}
    };

public:
    ~Grammar4()
    {
    }

    std::list<StackItem> Expand() override;
};