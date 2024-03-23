/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-23 19:32
 * @ Modified time: 2024-03-23 19:33
 */

#pragma once

#include "exception_base.hpp"
class InvalidCmdArguments : public ExceptionBase
{
public:
    InvalidCmdArguments(const std::string& message)
        : ExceptionBase(message)
    {
    }
};