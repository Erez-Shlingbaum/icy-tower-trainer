#pragma once

#include <cstddef>
#include <memory>
#include "process.hpp"

namespace OS
{
    template<typename T>
    class Symbol
    {
    public:
        Symbol(std::shared_ptr<Process> process, size_t offset) :
                _process(process), _offset(offset)
        {}

        Symbol &operator=(T value) const
        {
            _process->write_memory<T>(this->_offset, value);
            return this;
        }

        operator T() const
        {
            return _process->read_memory<T>(this->_offset);
        }

    private:
        std::shared_ptr<Process> _process;
        size_t _offset;
    };
}
