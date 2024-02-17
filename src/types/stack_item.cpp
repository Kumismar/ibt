#include "nonterminal.hpp"
#include "precedence_symbol.hpp"
#include "token.hpp"

bool StackItem::operator==(const StackItem& other) const
{
    if (this->itemType != other.itemType) {
        return false;
    }

    if (this->itemType == Nonterminal_t) {
        const Nonterminal* tmpThis = dynamic_cast<const Nonterminal*>(this);
        const Nonterminal* tmpOther = dynamic_cast<const Nonterminal*>(&other);
        return (*tmpThis == *tmpOther);
    }
    else if (this->itemType == Token_t) {
        const Token* tmpThis = dynamic_cast<const Token*>(this);
        const Token* tmpOther = dynamic_cast<const Token*>(&other);
        return (*tmpThis == *tmpOther);
    }
    else if (this->itemType == PrecSymbol_t) {
        const PrecedenceSymbol* tmpThis = dynamic_cast<const PrecedenceSymbol*>(this);
        const PrecedenceSymbol* tmpOther = dynamic_cast<const PrecedenceSymbol*>(&other);
        return (*tmpThis == *tmpOther);
    }

    return false;
}

bool StackItem::operator!=(const StackItem& other) const
{
    return !(*this == other);
}

ItemType StackItem::GetItemType() const
{
    return this->itemType;
}