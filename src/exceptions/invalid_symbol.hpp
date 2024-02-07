#pragma once

#include "exception_base.hpp"

class InvalidSymbolException : ExceptionBase
{
public:
    InvalidSymbolException(const std::string message)
        : ExceptionBase(message)
    {
    }
};