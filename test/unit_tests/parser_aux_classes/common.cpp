/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-29 09:16
 * @ Modified time: 2024-04-29 09:17
 */


#include "common.hpp"
#include "grammar.hpp"

bool handlesEqual(Rule& r1, Rule& r2)
{
    if (r1.size() != r2.size()) {
        return false;
    }

    auto it1 = r1.begin();
    auto it2 = r2.begin();
    for (; it1 != r1.end(); ++it1, ++it2) {
        if (**it1 != **it2) {
            return false;
        }
    }
    return true;
}

void cleanRule(Rule& rule)
{
    for (auto symb: rule) {
        delete symb;
    }
    rule.clear();
}