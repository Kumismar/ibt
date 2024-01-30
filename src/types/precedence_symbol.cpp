#include "precedence_symbol.hpp"

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
            this->precType = Invalid;
            break;
        }
    }
}

PrecedenceType PrecedenceSymbol::GetPrecedenceType() const
{
    return this->precType;
}