#pragma once

#include "Utils/common.h"
#include <chrono>
#include <thread>

typedef uint milliseconds;

class Timer
{
    bool started;
    std::chrono::steady_clock::time_point startTime;
public:
    Timer();
    void start();
    static void run(auto function, milliseconds after) {
        std::thread t([=]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(after));

            function();
        });
        t.detach();
    }
    uint timeInMilliseconds();
    void stop();
    void reset();
};
