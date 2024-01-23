#include "ll_table.hpp"
#include "nonterminal.hpp"
#include "nonterminal_type.hpp"
#include "token.hpp"

TableIndex RowAccessor::operator[](const Token& token) const
{
    return this->row[static_cast<unsigned>(token.GetTokenType())];
}

RowAccessor LLTable::operator[](const Nonterminal& nonTerminal) const
{
    return RowAccessor(this->table[static_cast<unsigned>(nonTerminal.GetType())]);
}