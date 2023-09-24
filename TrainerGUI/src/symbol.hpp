#pragma once

#include <cstddef>
#include <utility>
#include "process.hpp"

namespace OS
{
    template<typename T>
    class Symbol
    {
    public:
        // Symbol instances should be destroyed before process instance
        Symbol(Process &process, size_t offset) :
                _process(process), _offset(offset)
        {}

        Symbol &operator=(T value)
        {
            _process.write_memory<T>(this->_offset, value);
            return *this;
        }

        operator T() const
        {
            return _process.read_memory<T>(this->_offset);
        }

    private:
        Process &_process;
        size_t _offset;
    };
}
