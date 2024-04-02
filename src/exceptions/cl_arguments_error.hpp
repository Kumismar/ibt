/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-02 12:02
 * @ Modified time: 2024-04-02 12:03
 */

#pragma once

#include "exception_base.hpp"

class CLArgumentsError : public ExceptionBase
{
public:
    CLArgumentsError(const char* message)
        : ExceptionBase(message)
    {
    }
};
