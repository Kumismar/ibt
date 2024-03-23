/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-22 22:14
 * @ Modified time: 2024-03-23 17:38
 */

#include "stack_item.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "precedence_symbol.hpp"
#include "token.hpp"
#include <string>
#include <typeinfo>

bool Symbol::operator==(const Symbol& other) const
{
    if (this->symbType != other.GetSymbolType()) {
        return false;
    }

    if (this->symbType == Nonterminal_t) {
        const Nonterminal* tmpThis = dynamic_cast<const Nonterminal*>(this);
        const Nonterminal* tmpOther = dynamic_cast<const Nonterminal*>(&other);
        return (*tmpThis == *tmpOther);
    }
    else if (this->symbType == Token_t) {
        const Token* tmpThis = dynamic_cast<const Token*>(this);
        const Token* tmpOther = dynamic_cast<const Token*>(&other);
        return (*tmpThis == *tmpOther);
    }
    else if (this->symbType == PrecSymbol_t) {
        const PrecedenceSymbol* tmpThis = dynamic_cast<const PrecedenceSymbol*>(this);
        const PrecedenceSymbol* tmpOther = dynamic_cast<const PrecedenceSymbol*>(&other);
        return (*tmpThis == *tmpOther);
    }
    else {
        throw InternalError("Invalid Symbol type in Symbol::operator==(): \n" + std::string(typeid(*this).name()));
    }
}

bool Symbol::operator!=(const Symbol& other) const
{
    return !(*this == other);
}

SymbolType Symbol::GetSymbolType() const
{
    return this->symbType;
}