#include "exception_base.hpp"

const char* ExceptionBase::what() const noexcept
{
    return this->message.c_str();
}