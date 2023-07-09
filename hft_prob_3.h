#pragma once

#include <iostream>
#include <future>
#include <atomic>

#include "command.h"

// Output: foobar n time in order

class hft_prob_3 : public Command
{
    void printFoo(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            while(m_flag.load(std::memory_order_acquire) != 0){}
            std::cout << "Foo";
            m_flag.store(1, std::memory_order_release);
            m_Condvar.notify_one();
        }
    }
    void printBar(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            while(m_flag.load(std::memory_order_acquire) != 1){}
            std::cout << "Bar\n";
            m_flag.store(0, std::memory_order_release);
            m_Condvar.notify_one();
        }
    }

public:
    void execute()
    {
        auto fuBar = std::async(std::launch::async, &hft_prob_3::printBar, this, 10);
        auto fuFoo = std::async(std::launch::async, &hft_prob_3::printFoo, this, 10);

        fuBar.get();
        fuFoo.get();
    }
private:
    std::condition_variable m_Condvar;
    std::atomic_char m_flag;
};
