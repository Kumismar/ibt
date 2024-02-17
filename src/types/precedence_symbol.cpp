#include "precedence_symbol.hpp"
#include "internal_error.hpp"

PrecedenceSymbol::PrecedenceSymbol(char prec)
{
    switch (prec) {
        case '<': {
            this->precType = Push;
            break;
        }
        case '>': {
            this->precType = Reduce;
            break;
        }
        case '=': {
            this->precType = Equal;
            break;
        }
        default: {
            throw InternalErrorException("Invalid precedence symbol\n");
        }
    }
}

PrecedenceType PrecedenceSymbol::GetPrecedenceType() const
{
    return this->precType;
}

bool PrecedenceSymbol::operator==(const PrecedenceType& type) const
{
    return this->precType == type;
}
bool PrecedenceSymbol::operator==(const PrecedenceSymbol& other) const
{
    return this->precType == other.GetPrecedenceType();
}