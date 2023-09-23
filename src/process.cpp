#include "process.hpp"
#include "exceptions.hpp"

namespace OS
{
	Process::Process(const DWORD pid) :
		_handle(_open_process(pid))
	{
	}

	Buffer Process::read_memory(uintptr_t address, size_t amount) const
	{
		Buffer result{};
		result.resize(amount);
		_read_process_memory(address, amount, result.data());
		return result;
	}

	void Process::write_memory(uintptr_t address, std::span<const std::byte> bytes) const
	{
		if (!WriteProcessMemory(_handle, reinterpret_cast<LPVOID>(address), bytes.data(), bytes.size(), nullptr))
		{
			throw WindowsException();
		}
	}

	Handle Process::_open_process(const DWORD pid)
	{
		const HANDLE handle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
		if (handle == nullptr) { throw WindowsException(); }
		return Handle{ handle };
	}
	void Process::_read_process_memory(uintptr_t address, size_t amount, void* out_buffer) const
	{
		if (!ReadProcessMemory(_handle, reinterpret_cast<LPCVOID>(address), out_buffer, amount, nullptr))
		{
			throw WindowsException();
		}
	}
}
