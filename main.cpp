#include <iostream>
#include <memory>
#include "./command.h"
#include "./Test.h"

int main(int argc, char *argv[])
{
    std::unique_ptr<Command> obj;
    int prog = 1;//atoi(argv[1]);

    switch(prog){

       case 1:
       {
           obj.reset(new test_move());
       }
       break;
    }

    obj->execute();
    return 0;
}
