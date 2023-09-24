#include <utility>
#include "handle.hpp"

namespace OS
{
    Handle::Handle(const HANDLE handle) :
            _handle(handle)
    {}

    Handle::~Handle()
    {
        CloseHandle(_handle);
    }

    Handle::Handle(Handle &&other) noexcept :
            _handle(std::exchange(other._handle, INVALID_HANDLE_VALUE))
    {}

    Handle &Handle::operator=(Handle &&other) noexcept
    {
        _handle = std::exchange(other._handle, INVALID_HANDLE_VALUE);
        return *this;
    }

    Handle::operator HANDLE() const
    {
        return _handle;
    }
}
