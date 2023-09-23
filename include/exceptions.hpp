#pragma once

#include <Windows.h>
#include <stdexcept>

class WindowsException : std::runtime_error
{
public:
    explicit WindowsException(DWORD error_code = GetLastError()) :
            std::runtime_error(""), // TODO: get last error as string
            _error_code(error_code)
    {}

    [[nodiscard]] DWORD error_code() const
    {
        return _error_code;
    }

private:
    DWORD _error_code;
};
