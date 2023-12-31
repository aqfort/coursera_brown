#pragma once

#include <iostream>
#include <chrono>
#include <string>

class LogDuration
{
public:
    explicit LogDuration(const std::string &msg = std::string{})
        : message(msg), start(std::chrono::steady_clock::now()) {}
    ~LogDuration()
    {
        auto finish = std::chrono::steady_clock::now();
        auto dur = finish - start;
        auto s = duration_cast<std::chrono::seconds>(dur);
        dur -= s;
        auto ms = duration_cast<std::chrono::milliseconds>(dur);
        dur -= ms;
        auto us = duration_cast<std::chrono::microseconds>(dur);
        dur -= us;
        auto ns = duration_cast<std::chrono::nanoseconds>(dur);
        dur -= ns;
        if (!message.empty())
        {
            std::cerr << message << std::endl;
        }
        std::cerr << s.count() << " s "
                  << ms.count() << " ms "
                  << us.count() << " us "
                  << ns.count() << " ns "
                  << std::endl;
    }

private:
    std::string message;
    std::chrono::steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(line_no) _a_local_var_##line_no
#define UNIQ_ID(line_no) UNIQ_ID_IMPL(line_no)

#define LOG_DURATION(message) \
    LogDuration UNIQ_ID(__LINE__){message};
