#include <iostream>
#include <memory>
#include "./command.h"
#include "./sfine_example.h"
#include "./static_keys_map.h"
#include "./stdfunction_impl.h"
#include "./stdUnique_Impl.h"
#include "./ways_to_print_container.h"
#include "./stdRankImpl.h"
#include "./check_if_prime.h"
#include "./find_gcd.h"

int main(int argc, char *argv[])
{
    std::unique_ptr<Command> obj;
    int prog = atoi(argv[1]);

    switch(prog){

    case 1:
    {
        obj.reset(new sfine_example());
    }
        break;
    case 2:
    {
        obj.reset(new static_keys_map());
    }
        break;

    case 3:
    {
        obj.reset(new stdfunction_impl());
    }
        break;

    case 4:
    {
        obj.reset(new stdUnique_Impl());
    }
        break;
    case 5:
    {
        print_sequence(std::integer_sequence<unsigned, 9, 2, 5, 1, 9, 1, 6>{});
        printer(1, 2, 3, "abc");
    }
        break;
    case 6:
    {
        int a[1][1][1];
        static_assert(getDimention<decltype(a)>() == 3);
        static_assert(getDimention<int[]>() == 1);
        std::cout << "The tuple: " << std::make_tuple(2,'2',2.9) << '\n';
    }
        break;
    case 7:
    {
        static_assert(IsPrime<5>::value == true);
    }
        break;

    case 8:
    {
        static_assert(gcd<10,45>::value == euclid_mod(10,45));
    }
        break;
    }

    if (obj)
        obj->execute();
}
