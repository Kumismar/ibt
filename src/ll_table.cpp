#include "headers/ll_table.hpp"
#include "headers/nonterminal.hpp"
#include "headers/nonterminal_type.hpp"
#include "headers/token.hpp"

const TableIndex& RowAccessor::operator[](Token& token) const
{
    return this->row[(unsigned)(token.GetType())];
}

const RowAccessor LLTable::operator[](Nonterminal& nonterminal) const
{
    return RowAccessor(this->table[(unsigned)(nonterminal.GetType())]);
}