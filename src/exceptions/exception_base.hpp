/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-02-05 17:38
 * @ Modified time: 2024-03-23 17:32
 */

#pragma once

#include <exception>
#include <string>

class ExceptionBase : public std::exception
{
private:
    std::string message;

public:
    ExceptionBase() = default;
    ExceptionBase(const std::string& m)
        : message(m)
    {
    }

    const char* what() const noexcept override;
};