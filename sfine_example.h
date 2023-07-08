#pragma once

#include "command.h"
#include <iostream>
#include <string>
#include <array>
#include <string_view>
#include <string>
#include <cstddef>
#include <concepts>

//##
// When working with vendor libraries we cannot expect them to implement all APIs which may not be relevent for them
// Eg: vendor "B" might have written serialize() for struct "B" however vendor "A" would have implemented to_string("A")
// in Our code we need to create generic API serializeObejct() for both "A" and "B" at compile time
// How to do it?
//##
struct A {};
struct B {
   static std::string serialize() noexcept { return "I am B"; }
};
struct C {};

std::string to_string(const A& a) { return "I am A"; }
std::string to_string(const C& c) { return "I am C"; }

// Solution in C++ 17
template< typename C, typename = bool >
struct has_serialize
  : std::false_type
{};

template< typename C >
struct has_serialize< C, typename std::enable_if_t<
                         std::is_same_v<
                           decltype(C::serialize()),
                           std::string>, bool
                         >
                    >
  : std::true_type
{};

//(or if that non-static member function)

//template< typename C >
//struct has_serialize< C, typename std::enable_if_t<
//                         std::is_same_v<
//                           decltype(std::declval<const C&>().serialize()),
//                           std::string>, bool
//                         >
//                    >
//  : std::true_type
//{};

template<typename T>
static std::string serialize(T&& obj) {
    if constexpr (has_serialize<T>()){
        return obj.serialize();
    }else{
        return to_string(obj);
    }
}

// Solution in C++ 11/14
//template<typename T, std::enable_if_t<std::is_same_v<
//                                      decltype(to_string(std::declval<const T&>())),
//                                      std::string
//                                     >, void*> = nullptr>
//std::string serialize(T&& obj) {
//     T copy(obj);
//     return to_string(copy);
//}

//template<typename T, std::enable_if_t<std::is_same_v<
//                                      decltype(T::serialize()),
//                                      std::string
//                                     >, void*> = nullptr>
//std::string serialize(T&& obj) {
//    return obj.serialize();
//}

// Solution in C++ 17+
//template<typename T, std::enable_if_t<std::is_same_v<
//                                      std::void_t<decltype(to_string(std::declval<const T&>()))>, void
//                                     >, void*> = nullptr>
//std::string serialize(T&& obj) {
//     T copy(obj);
//     return to_string(copy);
//}

//template<typename T, std::enable_if_t<std::is_same_v<
//                                      std::void_t<decltype(T::serialize())>, void
//                                     >, void*> = nullptr>
//std::string serialize(T&& obj) {
//    return obj.serialize();
//}

// Solution in C++ 20
//template<typename T>
//concept has_serialize = std::is_same_v<std::void_t<decltype(T::serialize())>, void>;

//template<typename T>
//requires has_serialize<T>
//std::string serialize(T&& obj) {
//    return obj.serialize();
//}
//template<typename T>
//std::string serialize(T&& obj) {
//    T copy(obj);
//    return to_string(copy);
//}

template<typename Object>
std::string printSerializedObject(Object&& obj) {
    return serialize(std::forward<Object>(obj));
}

class sfine_example : public Command
{
public:
    void execute()
    {
        std::cout << printSerializedObject(A()) << std::endl;
//        std::cout << printSerializedObject(B()) << std::endl;
//        std::cout << printSerializedObject(C()) << std::endl;
    }
};
