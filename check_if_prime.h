#ifndef CHECK_IF_PRIME_H
#define CHECK_IF_PRIME_H

#include <iostream>

template<std::size_t T, std::size_t D = 2>
struct IsPrime
{
    static constexpr bool value = (T == D ? true : (T%D == 0 ? false : IsPrime<T, D + 1>::value));
};

template<std::size_t T>
struct IsPrime<T, T>
{
    static constexpr bool value = true;
};

template<std::size_t T>
struct IsPrime<1, T>
{
    static constexpr bool value = false;
};

#endif // CHECK_IF_PRIME_H
