#pragma once
#include <thread>
#include <chrono>

class MarketClock {
public:
    MarketClock(int delayMs) : delayMs(delayMs) {}

    void wait() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }

private:
    int delayMs;
};