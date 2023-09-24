#pragma once

#include <Windows.h>

namespace OS
{
    class Handle
    {
    public:
        explicit Handle(HANDLE handle);
        ~Handle();

        Handle(const Handle &) = delete;
        Handle &operator=(const Handle &) = delete;

        Handle(Handle && other) noexcept ;
        Handle &operator=(Handle && other) noexcept;

        operator HANDLE() const;

    private:
        HANDLE _handle;
    };
}
