#pragma once

#include "exception_base.hpp"

class EmptyStackException : public ExceptionBase
{
public:
    EmptyStackException(const std::string message)
        : ExceptionBase(message)
    {
    }
};