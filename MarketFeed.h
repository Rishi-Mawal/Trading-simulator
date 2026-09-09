#pragma once
#include <vector>
#include <iostream>
#include "DataLoader.h"
#include "MarketClock.h"
#include "IStrategy.h"

class MarketFeed {
public:
    MarketFeed(const std::vector<Bar>& bars, MarketClock& clock, IStrategy& strategy)
        : bars(bars), clock(clock), strategy(strategy) {}

    void play() {
        for (const Bar& bar : bars) {
            std::cout << bar.month << "/" << bar.day << "/" << bar.year
                      << " | Open: " << bar.open
                      << " | High: " << bar.high
                      << " | Low: " << bar.low
                      << " | Close: " << bar.close
                      << " | Volume: " << bar.volume << "\n";

            strategy.onBar(bar);

            clock.wait();
        }
    }

private:
    const std::vector<Bar>& bars;
    MarketClock& clock;
    IStrategy& strategy;
};