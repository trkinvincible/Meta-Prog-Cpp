//
// Created by thangar on 7/7/23.
//

#ifndef PRAC_META_PROG_VARIADIC_TEM_STD_UNIQUE_H
#define PRAC_META_PROG_VARIADIC_TEM_STD_UNIQUE_H

#include <type_traits>

template<int ... Args>
struct Vector;

// define the meta-function, seeding the output as an empty vector.
template <typename Input, typename Output = Vector<>>
struct uniq;

// define the partial specialization for recursion for filtering duplicates
template <int First, int... Rest, int... Result>
struct uniq<Vector<First, First, Rest...>, Vector<Result...>>
{
    // recurse without the duplicate first element and do not add
    // the duplicate to the result
    using type = typename uniq<Vector<First, Rest...>,
            Vector<Result...>>::type;
};

// define the partial specialization for recursion when no duplicates
// need filtering
template <int First, int... Rest, int... Result>
struct uniq<Vector<First, Rest...>, Vector<Result...>>
{
    // recurse without the first element and add the non-duplicate
    // to the result
    using type = typename uniq<Vector<Rest...>,
            Vector<Result..., First>>::type;
};

// define the partial specialization to terminate the recursion by
// assigning the now built up Output to the meta-function’s resulting type
template <typename Output>
struct uniq<Vector<>, Output>
{
    // Output is Vector<Result...> built up over previous recursion
    using type = Output;
};

#endif //PRAC_META_PROG_VARIADIC_TEM_STD_UNIQUE_H
