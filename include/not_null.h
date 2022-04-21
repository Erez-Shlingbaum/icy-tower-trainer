#pragma once

#include "exceptions.hpp"

namespace Utils
{
	template<typename T>
	T* not_null(T* value) 
	{
		if (value == nullptr)
		{
			throw NullPointerException();
		}
		return value;
	}

	template<typename T>
	class NotNull final
	{
	public:
		explicit NotNull(T* value) : _value(not_null(value))
		{
		}

		T* operator->() const noexcept
		{
			return this->_value;
		}

		T& operator*() const noexcept
		{
			return *this->_value;
		}

		T* get() const noexcept
		{
			return this->_value;
		}

	private:
		T* _value;
	};
}
