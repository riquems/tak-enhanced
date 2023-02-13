#include "Utils/Timer.hpp"

Timer::Timer() {
    this->started = false;
}

void Timer::start() {
    this->started = true;
    this->startTime = std::chrono::steady_clock::now();
}

uint Timer::timeInMilliseconds() {
    if (!this->started)
        return 0;

    auto now = std::chrono::steady_clock::now();
    return (std::chrono::duration_cast<std::chrono::milliseconds>(now - this->startTime).count());
}

void Timer::stop() {
    this->started = false;
    this->startTime = std::chrono::steady_clock::now();
}

void Timer::reset() {
    this->startTime = std::chrono::steady_clock::now();
}
