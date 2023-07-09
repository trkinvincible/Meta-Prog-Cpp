#pragma once

#include <iostream>
#include <future>
#include <atomic>

#include "command.h"

// Output: 0102030405... until n in order

class hft_prob_4 : public Command
{
    void zero()
    {
        std::cout << "0" << std::endl;
    }
    void even()
    {
        std::cout << "second" << std::endl;
    }
    void odd()
    {
        std::cout << "third" << std::endl;
    }

public:
    void execute()
    {
        auto fu0 = std::async(std::launch::async, &hft_prob_4::zero, this);
        auto fuE = std::async(std::launch::async, &hft_prob_4::even, this);
        auto fuO = std::async(std::launch::async, &hft_prob_4::odd, this);

        fu0.get();
        fuE.get();
        fuO.get();
    }
private:
    std::condition_variable m_Condvar;
    std::atomic_char m_flag;
};
