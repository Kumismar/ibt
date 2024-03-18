/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "precedence_symbol.hpp"
#include "token.hpp"
#include <string>
#include <typeinfo>

bool StackItem::operator==(const StackItem& other) const
{
    if (typeid(*this) != typeid(other)) {
        return false;
    }

    if (typeid(*this) == typeid(Nonterminal)) {
        const Nonterminal* tmpThis = dynamic_cast<const Nonterminal*>(this);
        const Nonterminal* tmpOther = dynamic_cast<const Nonterminal*>(&other);
        return (*tmpThis == *tmpOther);
    }
    else if (typeid(*this) == typeid(Token)) {
        const Token* tmpThis = dynamic_cast<const Token*>(this);
        const Token* tmpOther = dynamic_cast<const Token*>(&other);
        return (*tmpThis == *tmpOther);
    }
    else if (typeid(*this) == typeid(PrecedenceSymbol)) {
        const PrecedenceSymbol* tmpThis = dynamic_cast<const PrecedenceSymbol*>(this);
        const PrecedenceSymbol* tmpOther = dynamic_cast<const PrecedenceSymbol*>(&other);
        return (*tmpThis == *tmpOther);
    }
    else {
        // No StackItem instance should be created, only subclasses
        throw InternalErrorException("Invalid StackItem type in StackItem::operator==(): \n" + std::string(typeid(*this).name()));
    }
}

bool StackItem::operator!=(const StackItem& other) const
{
    return !(*this == other);
}