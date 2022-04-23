#pragma once
#include <vector>

#include "handle.hpp"
#include "trivial.hpp"

namespace OS
{
	using Buffer = std::vector<uint8_t>;

	class Process
	{
	public:
		explicit Process(DWORD pid);

		// Should throw if cannot return correct amount
		[[nodiscard]] Buffer read_memory(uintptr_t address, size_t amount) const;

		template <Trivial T>
		[[nodiscard]] T read_memory(const uintptr_t address)
		{
			Buffer bytes = read_memory(address, sizeof(T));
			T result{};
			std::copy(bytes.begin(), bytes.end(), &result);
			return result;
		}

		void write_memory(uintptr_t address, const Buffer& bytes) const;

	private:
		static Handle _open_process(DWORD pid);

		Handle _handle;
	};
}
