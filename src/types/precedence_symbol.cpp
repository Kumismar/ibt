#include "precedence_symbol.hpp"
#include "internal_error.hpp"
#include "stack_item.hpp"

PrecedenceSymbol::PrecedenceSymbol(PrecedenceType type)
{
    this->precType = type;
    this->itemType = PrecSymbol_t;
}

PrecedenceType PrecedenceSymbol::GetPrecedenceType() const
{
    return this->precType;
}

std::string PrecedenceSymbol::GetTypeString() const
{
    switch (this->precType) {
        case Push:
            return "<";
        case Reduce:
            return ">";
        case Equal:
            return "=";
        default:
            throw InternalErrorException("Invalid PrecedenceSymbol type in PrecedenceSymbol::GetTypeString()\n");
    }
}

bool PrecedenceSymbol::operator==(const PrecedenceType& type) const
{
    return this->precType == type;
}
bool PrecedenceSymbol::operator==(const PrecedenceSymbol& other) const
{
    return this->precType == other.GetPrecedenceType();
}