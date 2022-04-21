#pragma once

#include <stdexcept>

class NullPointerException : public std::exception
{
public:
	using std::exception
};
