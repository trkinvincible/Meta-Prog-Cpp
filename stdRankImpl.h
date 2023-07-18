#pragma once

#include <type_traits>

template<class T>
struct rank : public std::integral_constant<std::size_t, 0> {};

template<class T>
struct rank<T[]> : public std::integral_constant<std::size_t, rank<T>::value + 1> {};

template<class T, std::size_t N>
struct rank<T[N]> : public std::integral_constant<std::size_t, rank<T>::value + 1> {};


template<typename Container>
consteval int getDimention()
{
   return rank<Container>::value;
}


