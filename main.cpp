#include <iostream>
#include <memory>
#include "./command.h"
#include "./hft_prob_1.h"
#include "./hft_prob_2.h"
#include "./hft_prob_3.h"

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
    case 2:
    {
        obj.reset(new hft_prob_2());
    }
        break;

    case 3:
    {
        obj.reset(new hft_prob_3());
    }
        break;
    }

    if (obj)
        obj->execute();
}
