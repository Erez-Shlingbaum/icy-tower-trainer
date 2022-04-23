#pragma once

#include <type_traits>

template <class T>
concept Trivial = std::is_trivial_v<T>;
