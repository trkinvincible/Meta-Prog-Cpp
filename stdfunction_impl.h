#ifndef STDFUNCTION_IMPL_H
#define STDFUNCTION_IMPL_H

#include <iostream>
#include <functional>

#include "command.h"

namespace Rk{

template<typename T>
struct myfunction;

template<typename Ret, typename ...Params>
struct myfunction<Ret(Params... params)>
{
public:
    myfunction(Ret(*func)(Params...))
        :m_Func(func){ }

    Ret operator()(Params ... params)
    {
        return m_Func(params ...);
    }

private:
    Ret(*m_Func)(Params...);
};


}

using namespace Rk;

int returnInt(int a, float b)
{
    return a + b;
}

class stdfunction_impl : public Command
{
public:
    void execute()
    {
        myfunction<int(int, float)> func1{returnInt};
        std::cout << func1(5, 5.5) << std::endl;

        myfunction<char*(char*)> func2{[](char* a)->char*{ return a; }};
        std::cout << func2("5") << std::endl;
    }
};

#endif // STDFUNCTION_IMPL_H
