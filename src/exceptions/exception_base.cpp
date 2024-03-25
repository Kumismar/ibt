/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-02-05 17:44
 * @ Modified time: 2024-03-23 17:32
 */

#include "exception_base.hpp"

const char* ExceptionBase::what() const noexcept
{
    return this->message.c_str();
}