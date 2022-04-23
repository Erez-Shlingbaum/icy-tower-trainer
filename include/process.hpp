#pragma once
#include <span>
#include <vector>

#include "handle.hpp"
#include "trivial.hpp"

namespace OS
{
	using Byte = uint8_t;
	using Buffer = std::vector<Byte>;

	class Process
	{
	public:
		/**
		 * \throws WindowsException
		 */
		explicit Process(DWORD pid);

		/**
		 * \throws WindowsException
		 */
		[[nodiscard]] Buffer read_memory(uintptr_t address, size_t amount) const;

		/**
		 * \throws WindowsException
		 */
		template <Trivial T>
		[[nodiscard]] T read_memory(const uintptr_t address)
		{
			Buffer bytes = read_memory(address, sizeof(T));
			T result{};
			std::copy(bytes.begin(), bytes.end(), &result);
			return result;
		}

		/**
		 * \throws WindowsException
		 */
		void write_memory(uintptr_t address, std::span<const Byte> bytes) const;

		/**
		 * \throws WindowsException
		 */
		template <Trivial T>
		void write_memory(uintptr_t address, const T& data) const
		{
			write_memory(address, std::span{data, sizeof(data)});
		}


	private:
		/**
		 * \throws WindowsException
		 */
		static Handle _open_process(DWORD pid);

		Handle _handle;
	};
}
