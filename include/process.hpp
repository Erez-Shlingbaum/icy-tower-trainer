#pragma once
#include <span>
#include <vector>

#include "handle.hpp"

namespace OS
{
	using Buffer = std::vector<std::byte>;

	class Process
	{
	public:
		explicit Process(DWORD pid);

		[[nodiscard]] Buffer read_memory(uintptr_t address, size_t amount) const;

		template <typename T> requires (std::is_trivial_v<T>)
		[[nodiscard]] T read_memory(const uintptr_t address)
		{
			T result{};
			_read_process_memory(address, sizeof(T), &result);
			return result;
		}

		void write_memory(uintptr_t address, std::span<const std::byte> bytes) const;

		template <typename T> requires (std::is_trivial_v<T>)
		void write_memory(uintptr_t address, const T& data) const
		{
			write_memory(address, std::span{data, sizeof(data)});
		}


	private:
		static Handle _open_process(DWORD pid);
		void _read_process_memory(uintptr_t address, size_t amount, void* out_buffer) const;

		Handle _handle;
	};
}
