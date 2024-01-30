#include "ll_table.hpp"
#include "nonterminal.hpp"
#include "token.hpp"

LLTableIndex LLRowAccessor::operator[](const Token& t) const
{
    return this->row[static_cast<unsigned>(t.GetTokenType())];
}

LLRowAccessor LLTable::operator[](const Nonterminal& nt) const
{
    return LLRowAccessor(this->table[static_cast<unsigned>(nt.GetNonterminalType())]);
}