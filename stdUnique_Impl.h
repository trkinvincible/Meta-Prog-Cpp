#ifndef STDUNIQUE_IMPL_H
#define STDUNIQUE_IMPL_H

#include <iostream>

#include "command.h"

#include "constexpr_std_unique_stl.h"
//#include "fold_expr_std_unique.h"
//#include "variadic_tem_std_unique.h"
//#include "ways_to_print_container.h"

namespace Rk{


}

using namespace Rk;

class stdUnique_Impl : public Command
{
public:
    void execute()
    {
        // In c++ 20 std::vector and std::string are made constexpr because there are constexpr new and constexpr delete
        // which means i can allocate a vector in constexpr context but it cannot be allowed to escape into non-constexpr context\
        // eg: constexpr vec = some_constexpr_return_vector();

        static_assert(std::is_same_v<uniq<Vector<1, 2, 2, 2, 3, 4, 4>>::type,
                    Vector<1, 2, 3, 4>>);

        // https://www.mavensecurities.com/revisiting-interview-questions-at-maven/
    }
};



#endif // STDUNIQUE_IMPL_H
