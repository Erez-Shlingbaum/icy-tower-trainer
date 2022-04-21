#pragma once

#include <Windows.h>

namespace OS
{
	class Handle
	{
	public:
		explicit Handle(HANDLE handle);

		~Handle();

		Handle(const Handle&) = delete;
		Handle& operator=(const Handle&) = delete;

		Handle(Handle&&) = default;
		Handle& operator=(Handle&&) = default;

	private:
		HANDLE _handle;
	};
}
