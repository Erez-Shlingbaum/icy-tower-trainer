#pragma once

#include <iterator>
#include <stdexcept>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

#include "handle.hpp"
#include "os_utils.hpp"

namespace OS
{
	class ProcessList
	{
	public:
		class Iterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = PROCESSENTRY32;
			using pointer = PROCESSENTRY32*;
			using reference = PROCESSENTRY32&;
			using difference_type = size_t;

			Iterator();
			explicit Iterator(HANDLE snapshot_handle);

			Iterator& operator++();

			PROCESSENTRY32 operator*() const;
			const PROCESSENTRY32* operator->() const;

			friend bool operator==(const Iterator& lhs, const Iterator& rhs);

			friend bool operator!=(const Iterator& lhs, const Iterator& rhs);

		private:
			HANDLE _snapshot_handle;
			PROCESSENTRY32 _process_entry;
			bool _is_iterator_consumed;
		};

		ProcessList();

		[[nodiscard]] Iterator begin() const;
		[[nodiscard]] static Iterator end() ;

	private:
		[[nodiscard]] static Handle _create_snapshot();

		Handle _snapshot_handle;
	};

	std::vector<PROCESSENTRY32> get_running_processes();
}
