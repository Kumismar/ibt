#include "ll_table.hpp"
#include "nonterminal.hpp"
#include "nonterminal_type.hpp"
#include "token.hpp"

const TableIndex RowAccessor::operator[](Token& token) const
{
    return this->row[(unsigned)(token.GetTokenType())];
}

const RowAccessor LLTable::operator[](Nonterminal& nonterminal) const
{
    return RowAccessor(this->table[(unsigned)(nonterminal.GetType())]);
}