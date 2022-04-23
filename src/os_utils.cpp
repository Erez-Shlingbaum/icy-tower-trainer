#include "os_utils.hpp"
#include "exceptions.hpp"

namespace OS
{
	ProcessList::Iterator::Iterator():
		_snapshot_handle(),
		_process_entry(),
		_is_iterator_consumed(true)
	{
	}

	ProcessList::Iterator::Iterator(const HANDLE snapshot_handle) :
		_snapshot_handle(snapshot_handle),
		_process_entry(),
		_is_iterator_consumed(false)
	{
		_process_entry.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(_snapshot_handle, &_process_entry)) { throw WindowsException(); }
	}

	ProcessList::Iterator& ProcessList::Iterator::operator++()
	{
		if (_is_iterator_consumed) { throw std::logic_error("Trying to advance a consumed iterator"); }
		if (!Process32Next(_snapshot_handle, &_process_entry)) { _is_iterator_consumed = true; }
		return *this;
	}

	PROCESSENTRY32 ProcessList::Iterator::operator*() const { return _process_entry; }

	const PROCESSENTRY32* ProcessList::Iterator::operator->() const { return &_process_entry; }

	ProcessList::ProcessList():
		_snapshot_handle(_create_snapshot())
	{
	}

	ProcessList::Iterator ProcessList::begin() const { return Iterator{_snapshot_handle}; }

	ProcessList::Iterator ProcessList::end() const { return Iterator{}; }

	Handle ProcessList::_create_snapshot()
	{
		const HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot_handle == INVALID_HANDLE_VALUE) { throw WindowsException(); }
		return Handle{snapshot_handle};
	}

	std::vector<PROCESSENTRY32> get_running_processes()
	{
		const ProcessList process_list{};

		std::vector<PROCESSENTRY32> result{};
		std::copy(process_list.begin(), process_list.end(), std::back_inserter(result));

		return result;
	}
}