#pragma once

#include "exception_base.hpp"

class InternalErrorException : ExceptionBase
{
public:
    InternalErrorException(const std::string& message)
        : ExceptionBase(message)
    {
    }
};