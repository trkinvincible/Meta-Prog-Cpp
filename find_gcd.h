#pragma once

#include <cstdio>
#include <utility>
#include <iostream>

consteval int euclid_mod(int a, int b) {
  if (b == 0)
    return a;
  return euclid_mod(b, a%b);
}

template<std::size_t T1, std::size_t T2>
struct gcd
{
	static constexpr std::size_t value = gcd<T2, T1%T2>::value;
};

template<std::size_t T1>
struct gcd <T1, 0>
{
	static constexpr auto value = T1;
};
