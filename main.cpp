#include <iostream>
#include <memory>
#include "./command.h"
#include "./hft_prob_1.h"

int main(int argc, char *argv[])
{
    std::unique_ptr<Command> obj;
    int prog = atoi(argv[1]);

    switch(prog){

    case 1:
    {
        obj.reset(new hft_prob_1());
    }
        break;
    }
    if (obj)
        obj->execute();
}
