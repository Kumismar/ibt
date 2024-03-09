#pragma once

#include "exception_base.hpp"

class LexicalErrorException : public ExceptionBase
{
public:
    LexicalErrorException(const std::string& message)
        : ExceptionBase(message)
    {
    }
};