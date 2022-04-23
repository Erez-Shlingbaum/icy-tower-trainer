#include "handle.hpp"

namespace OS
{
	Handle::Handle(const HANDLE handle) :
		_handle(handle)
	{
	}

	Handle::~Handle() { CloseHandle(_handle); }

	Handle::operator HANDLE() const { return _handle; }
}
