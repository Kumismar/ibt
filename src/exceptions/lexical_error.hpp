/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-11 12:42
 * @ Modified time: 2024-03-23 19:33
 */

#pragma once

#include "exception_base.hpp"

class LexicalError : public ExceptionBase
{
public:
    LexicalError(const std::string& message)
        : ExceptionBase(message)
    {
    }
};