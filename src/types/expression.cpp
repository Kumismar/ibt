#include "expression.hpp"
#include "nonterminal.hpp"
#include "token.hpp"

bool Expression::operator==(const Expression& other) const
{
    if (this->expType != other.expType) {
        return false;
    }

    if (this->expType == ExpNonterminal) {
        const Nonterminal& tmpThis = dynamic_cast<const Nonterminal&>(*this);
        const Nonterminal& tmpOther = dynamic_cast<const Nonterminal&>(other);
        return (tmpThis == tmpOther);
    }
    else if (this->expType == ExpToken) {
        const Token& tmpThis = dynamic_cast<const Token&>(*this);
        const Token& tmpOther = dynamic_cast<const Token&>(other);
        return (tmpThis == tmpOther);
    }

    return false;
}

bool Expression::operator!=(const Expression& other) const
{
    return !(*this == other);
}

ExpressionType Expression::GetExpressionType() const
{
    return this->expType;
}