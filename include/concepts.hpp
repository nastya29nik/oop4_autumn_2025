#pragma once

#include <concepts>
#include <type_traits>


template <class T>
concept Scalar = std::is_arithmetic_v<T>;