#pragma once

#include <charconv>
#include <iostream>
#include <future>

#include "command.h"

// Output: firstsecondthird in order

class hft_prob_2 : public Command
{
    void first()
    {
        while(m_order.load(std::memory_order_acquire) != 1){}
        std::cout << "first" << std::endl;
        m_order.fetch_add(1, std::memory_order_acq_rel);
    }
    void second()
    {
        while(m_order.load(std::memory_order_acquire) != 2){}
        std::cout << "second" << std::endl;
        m_order.fetch_add(1, std::memory_order_acq_rel);
    }
    void third()
    {
        while(m_order.load(std::memory_order_acquire) != 3){}
        std::cout << "third" << std::endl;
        m_order.fetch_add(1, std::memory_order_acq_rel);
    }

public:
    void execute()
    {
        auto fuC = std::async(std::launch::async, &hft_prob_2::third, this);
        auto fuB = std::async(std::launch::async, &hft_prob_2::second, this);
        auto fuA = std::async(std::launch::async, &hft_prob_2::first, this);
        fuA.get();
        fuB.get();
        fuC.get();
    }
private:
    std::atomic<std::uint8_t> m_order{1};
};
