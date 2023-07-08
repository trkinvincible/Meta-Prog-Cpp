#ifndef STATICKEYSMAP_H
#define STATICKEYSMAP_H

#include <array>
#include <string_view>

#include "command.h"

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

class static_keys_map : public Command
{
public:
    void execute()
    {
        GetValue<Key_of_0>(); // this will compile
        //GetValue<Key_of_dummy>(); // this will not compile
    }
};

#endif // STATICKEYSMAP_H
