#include <iostream>
#include "DataLoader.h"
#include "MarketClock.h"
#include "MarketFeed.h"
#include "Portfolio.h"
#include "SimpleDipBuyer.h"

int main() {
    std::vector<Bar> allBars = loadData("data/aapl.csv");
    std::cout << "Loaded " << allBars.size() << " total bars.\n";

    std::vector<Bar> bars = getRecentBars(allBars, 630);
    std::cout << "Using most recent " << bars.size() << " bars.\n\n";

    MarketClock clock(500);
    Portfolio portfolio(10000.0); // start with $10000 fake cah
    SimpleDipBuyer strategy(portfolio);
    MarketFeed feed(bars, clock, strategy);

    feed.play();

    double finalPrice = bars.back().close;
    portfolio.printSummary(finalPrice);

    return 0;
}
