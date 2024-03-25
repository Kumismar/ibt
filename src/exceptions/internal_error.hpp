/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-04 21:33
 * @ Modified time: 2024-03-23 19:33
 */

#pragma once

#include "exception_base.hpp"

class InternalError : public ExceptionBase
{
public:
    InternalError(const std::string message)
        : ExceptionBase(message)
    {
    }
};