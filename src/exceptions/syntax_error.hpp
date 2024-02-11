#pragma once

#include "exception_base.hpp"

class SyntaxErrorException : public ExceptionBase
{
public:
    SyntaxErrorException(const std::string& message)
        : ExceptionBase(message)
    {
    }
};