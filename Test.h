#pragma once
#include "command.h"
#include <string>
#include <array>
#include <string_view>

//##
// add constexpr varaibles
// usecase: say i have a map of <keys, Values> keys i know in compile time itself. With this implementation can easily catch wrong query into map
// also map construction is done at compile time which will boost bootup performance.
//##
namespace Rk{
    static constexpr char Key_of_0[] = "123";
    static constexpr char Key_of_1[] = "456";
    static constexpr char Key_of_2[] = "789";
    static constexpr std::array<std::string_view, 3> Keys{Key_of_0, Key_of_1, Key_of_2};

    static constexpr char Key_of_dummy[] = "000";

    template<const char* key>
    constexpr bool isValidKey(){
        for (const auto& i : Keys){
            if (key == i)
                return true;
        }
        return false;
    }
}
using namespace Rk;

template<const char* key>
void GetValue(){

    static_assert(isValidKey<key>(), "key specified must be from the one defined in that map");
    //.. proceed further
}

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
std::string serialize(T&& obj) {
    if constexpr (has_serialize<T>()){
        return obj.serialize();
    }else{
        T copy(obj);
        return to_string(copy);
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

template<typename Object>
std::string printSerializedObject(Object&& obj) {
    return serialize(std::forward<Object>(obj));
}

class test_move : public Command
{
public:
    void execute()
    {
        GetValue<Key_of_0>(); // this will compile
        //GetValue<Key_of_dummy>(); // this will not compile

        std::cout << printSerializedObject(A()) << std::endl;
        std::cout << printSerializedObject(B()) << std::endl;
        std::cout << printSerializedObject(C()) << std::endl;
    }
};
