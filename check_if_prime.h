#pragma once

#include <iostream>

#if 0
template<std::size_t T, std::size_t D = 2>
struct IsPrime
{
    static constexpr bool value = T == D ? true : (T%D == 0 ? false : IsPrime<T, D + 1>::value);
};

template<std::size_t T>
struct IsPrime<T, T>
{
    static constexpr bool value = true;
};
#else
template<std::size_t T, std::size_t D = 2>
struct IsPrime
{
    static constexpr bool value = []() {
      if constexpr (T == D)
        return true;
      else if constexpr (T%D == 0)
        return false;
      else
        return IsPrime<T, D + 1>::value;
    }();
};
#endif

template<std::size_t T>
struct IsPrime<2, T>
{
    static constexpr bool value = true;
};
template<std::size_t T>
struct IsPrime<1, T>
{
    static constexpr bool value = false;
};
