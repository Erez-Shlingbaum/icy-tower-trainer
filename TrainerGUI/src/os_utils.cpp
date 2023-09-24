#include "os_utils.hpp"
#include "exceptions.hpp"

namespace OS
{
    ProcessSnapshot::Iterator::Iterator() :
            _snapshot_handle(),
            _process_entry(),
            _is_iterator_consumed(true)
    {}

    ProcessSnapshot::Iterator::Iterator(const HANDLE snapshot_handle) :
            _snapshot_handle(snapshot_handle),
            _process_entry(),
            _is_iterator_consumed(false)
    {
        _process_entry.dwSize = sizeof(PROCESSENTRY32);
        if (!Process32First(_snapshot_handle, &_process_entry))
        {
            throw WindowsException();
        }
    }

    ProcessSnapshot::Iterator &ProcessSnapshot::Iterator::operator++()
    {
        if (_is_iterator_consumed)
        {
            throw std::logic_error("Trying to advance a consumed iterator");
        }
        if (!Process32Next(_snapshot_handle, &_process_entry))
        {
            _is_iterator_consumed = true;
        }
        return *this;
    }

    PROCESSENTRY32 ProcessSnapshot::Iterator::operator*() const
    {
        return _process_entry;
    }

    const PROCESSENTRY32 *ProcessSnapshot::Iterator::operator->() const
    {
        return &_process_entry;
    }

    bool operator==(const ProcessSnapshot::Iterator &lhs, const ProcessSnapshot::Iterator &rhs)
    {
        return lhs._is_iterator_consumed == rhs._is_iterator_consumed;
    }

    bool operator!=(const ProcessSnapshot::Iterator &lhs, const ProcessSnapshot::Iterator &rhs)
    {
        return !(lhs == rhs);
    }

    ProcessSnapshot::ProcessSnapshot() :
            _snapshot_handle(_create_snapshot())
    {}

    ProcessSnapshot::Iterator ProcessSnapshot::begin() const
    {
        return Iterator{_snapshot_handle};
    }

    ProcessSnapshot::Iterator ProcessSnapshot::end()
    {
        return Iterator{};
    }

    Handle ProcessSnapshot::_create_snapshot()
    {
        const HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot_handle == INVALID_HANDLE_VALUE)
        {
            throw WindowsException();
        }
        return Handle{snapshot_handle};
    }

    std::vector<PROCESSENTRY32> get_running_processes()
    {
        const ProcessSnapshot process_list{};
        return std::vector<PROCESSENTRY32>{process_list.begin(), process_list.end()};
    }
}
