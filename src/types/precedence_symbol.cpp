#include "precedence_symbol.hpp"
#include "internal_error.hpp"
#include "stack_item.hpp"

PrecedenceSymbol::PrecedenceSymbol(const PrecedenceType type)
    : precType(type)
{
}

PrecedenceSymbol::PrecedenceSymbol(const PrecedenceSymbol& old)
    : precType(old.GetPrecedenceType())
{
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

StackItem* PrecedenceSymbol::Clone() const
{
    return new PrecedenceSymbol(*this);
}