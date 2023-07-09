#pragma once

#include <iostream>

template<typename... Args>
void printer(Args&&... args)
{
    // lhs + ... + rhs
    // in this case lhs's (iostream) "operator <<" for all types of rhs must have been defined.
    (std::cout << ... << args) << '\n';
}

// debugging aid
template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    // comma operator is used to separate the arguments.
    ((std::cout << ints << ' '), ...);
    std::cout << '\n';
}

