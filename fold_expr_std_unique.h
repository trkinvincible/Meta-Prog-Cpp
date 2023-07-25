#pragma once

#include <type_traits>
#include <utility>
#include <tuple>

template <int... I>
struct Vector {};

template <typename Vector>
struct uniq; // Primary template

template <int... I>
struct uniq<Vector<I...>>
{
    // Vector<1, 2, 3> this is whole new type forget about the traditional data inside the vector.
    using type = decltype((Vector<>{} + ... + std::integral_constant<int, I>{}));
};

template <typename ...Args>
constexpr auto last(Args ...args)
{
    constexpr auto identity = [](auto i) { return i; };
    // fold expression with comma operator separates the arguments.
    //return (args, ...); // will work but with warning that return variables are ignored.
    return (identity(args), ...);
}


//template <int... I>
//consteval auto last(Vector<I...>)
//{
//    constexpr std::tuple t{I...};
//    constexpr auto N = std::tuple_size_v<decltype(t)>;
//    return std::get<N-1>(t);
//}

// this is defined as folder expression is unfolded with + operator in line:16 with left operand as vector
// and right operand as unpacked integral_constant.
template <int... I, int X>
constexpr auto operator+(Vector<I...> v, std::integral_constant<int, X> x)
{
    if constexpr (sizeof...(I) == 0)
    {
        return Vector<X>{};
    }
    else if constexpr (last(I...) == x)
    {
        return v;
    }
    else
    {
        return Vector<I..., X>{};
    }
}
