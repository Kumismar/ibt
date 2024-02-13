#pragma once

#include <stdexcept>

class ExceptionBase : public std::exception
{
private:
    std::string message;

public:
    ExceptionBase(const std::string& m)
        : message(m)
    {
    }

    const char* what() const noexcept override;
};