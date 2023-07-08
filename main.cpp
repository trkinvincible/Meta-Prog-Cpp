#include <iostream>
#include <memory>
#include "./command.h"
#include "./sfine_example.h"
#include "./static_keys_map.h"
#include "./stdfunction_impl.h"
#include "./stdUnique_Impl.h"
#include "./ways_to_print_container.h"

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
    }

    if (obj)
        obj->execute();
}
