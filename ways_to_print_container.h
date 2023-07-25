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

// pretty-print a tuple
template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch,Tr>& os,
                      const Tuple& t,
                      std::index_sequence<Is...>)
{
    ((os << (Is == 0? "" : ", ") << std::get<Is>(t)), ...);
}

//template<class Ch, class Tr, class... Args>
//auto& operator<<(std::basic_ostream<Ch, Tr>& os,
//                 const std::tuple<Args...>& t)
//{
//    os << "(";
//    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
//    return os << ")";
//}

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& theTuple)
{
    std::apply
    (
        [&os](Ts const&... tupleArgs)
        {
            os << '[';
            std::size_t n{0};
            ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
            os << ']';
        }, theTuple
    );
    return os;
}
