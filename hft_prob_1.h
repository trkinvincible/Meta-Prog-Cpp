#pragma once

#include <charconv>
#include <iostream>
#include <mutex>
#include <future>
#include <vector>
#include <sstream>

#include "command.h"

//Wite a program which takes three inputs (command line)
//1. A string
//2. char count (integer)
//3. thread count no of Threads(integer).

//Each thread then should start printing the chars in the string sequentially in the following format:
//> myprinter ABCDEFGHIJ 3 4
//outPut:
//Using 4 threads to print ABC DEFGHIJ alternatively in set of 3 chars
//Thread1: ABC
//Thread2: DEF
//Thread3: GHI
//Thread4: JAB
//Thread1: CDE
//Thread2: EGH
//Thread3: IJE

class hft_prob_1 : public Command
{
public:
    void print(const std::string& text)
    {
        std::lock_guard mu(m_CoutGuard);
        std::cout << text << std::endl;
    }

    void execute()
    {
        static constexpr char* argv[]={"myprinter","ABCDEFGHIJ","3","4"};
        std::string_view inputString{argv[1]};
        std::string_view charCountStr{argv[2]};
        std::string_view threadCountStr{argv[3]};

        std::size_t charCount{};
        if (const auto& [ptr, ec] = std::from_chars(charCountStr.data(), charCountStr.data() + charCountStr.size(), charCount);
            (ec != std::errc() || charCount == 0))
        {
            std::cerr << "invalid char count." << std::make_error_code(ec).message() << std::endl;
            exit(1);
        }
        std::size_t threadCount{};
        if (const auto& [ptr, ec] = std::from_chars(threadCountStr.data(), threadCountStr.data() + threadCountStr.size(), threadCount);
            (ec != std::errc() || threadCount == 0))
        {
            std::cerr << "invalid char count." << std::make_error_code(ec).message() << std::endl;
            exit(1);
        }

        // How many loops all 4 threads must print. say, 2.
        for (int i = 0; i < 2; ++i)
        {
            for (std::size_t j = 0; j < threadCount; ++j)
            {
                // this is truely async processing the string.
                // Input String must be passed as individual copy or if its a file do DMA and on demand paging
                // to avoid false sharing.
                auto start = (j * charCount) + (i * (threadCount * charCount) % inputString.length());
                auto fu = std::async(std::launch::async, [=, startOffset = start, threadNo = j]() mutable
                {
                    // Single responsibility. Thread should not decide who must go next. Its resposibility to to print.
                    std::stringstream ss;
                    ss << "Thread" << threadNo + 1 << ":" << " ";
                    for (int k = 0; k < charCount; ++k,++startOffset)
                    {
                        auto index = (startOffset % inputString.length());
                        ss << inputString[index];
                    }
                    print(ss.str());
                });
            }
        }
    }
private:
    std::mutex m_CoutGuard;
};
