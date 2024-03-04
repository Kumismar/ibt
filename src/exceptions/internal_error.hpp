#pragma once

#include "exception_base.hpp"

class InternalErrorException : public ExceptionBase
{
public:
    InternalErrorException(const std::string message)
        : ExceptionBase(message)
    {
    }
};