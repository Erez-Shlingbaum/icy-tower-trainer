#pragma once
#include <cstddef>

namespace OS {

	template <typename T>
	class Symbol
	{
	public:
		Symbol(std::shared_ptr<Process> process, size_t offset) :
			_process(process), _offset(offset)
		{
		}

		Symbol& operator=(T value) const
		{
			process.write_memory<T>(this._offset, value);
			return this;
		}

		operator T() const
		{
			return process.read_memory<T>(this._offset);
		}
	private:
		const std::shared_ptr<Process> _process;
		const size_t _offset;
	};
}
