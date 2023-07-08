//
// Created by thangar on 7/7/23.
//

#ifndef PRAC_META_PROG_CONSTEXPR_STD_UNIQUE_STL_H
#define PRAC_META_PROG_CONSTEXPR_STD_UNIQUE_STL_H

#include <algorithm>
#include <type_traits>
#include <utility>

template <int... I>
struct Vector {};

template <typename Vector>
struct uniq; // Primary template

template<int... I> struct uniq<Vector<I...>>
{
    static auto constexpr uniqueValues = []{
        struct { int data[sizeof...(I)]; int size; } r{{I...}, sizeof...(I)};
        // constexpr version of std::unique is not available in C++20.
        r.size = std::unique(r.data, r.data + r.size) - r.data;
        return r;
    }();

    static auto constexpr toTypeSpace = []<auto p>(){
        return []<std::size_t... J>(std::index_sequence<J...>) {
            return Vector<p.data[J]...>();
        }(std::make_index_sequence<p.size>());
    };

    using type = decltype(toTypeSpace.template operator()<uniqueValues>());
};

#endif //PRAC_META_PROG_CONSTEXPR_STD_UNIQUE_STL_H
