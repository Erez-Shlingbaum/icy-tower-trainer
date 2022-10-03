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
			using difference_type = std::ptrdiff_t;


			Iterator();
			explicit Iterator(const HANDLE snapshot_handle);

			Iterator& operator++();

			const PROCESSENTRY32& operator*() const;
			const PROCESSENTRY32* operator->() const;

			friend bool operator==(const Iterator& lhs, const Iterator& rhs)
			{
				return lhs._is_iterator_consumed == rhs._is_iterator_consumed;
			}

			friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }

			friend bool operator<(const Iterator& lhs, const Iterator& rhs)
			{
				return lhs._is_iterator_consumed != rhs._is_iterator_consumed;
			}

			friend bool operator<=(const Iterator& lhs, const Iterator& rhs) { return !(rhs < lhs); }
			friend bool operator>(const Iterator& lhs, const Iterator& rhs) { return rhs < lhs; }
			friend bool operator>=(const Iterator& lhs, const Iterator& rhs) { return !(lhs < rhs); }

		private:
			HANDLE _snapshot_handle;
			PROCESSENTRY32 _process_entry;
			bool _is_iterator_consumed;
		};

		ProcessList();

		Iterator begin() const;
		Iterator end() const;

	private:
		static Handle _create_snapshot();

		Handle _snapshot_handle;
	};
}
