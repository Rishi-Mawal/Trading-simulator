#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Trade {
    std::string type; // "BUY" or "SELL"
    std::string date;
    double price;
    int shares;
};

class Portfolio {
public:
    Portfolio(double startingCash)
        : cash(startingCash), sharesHeld(0), buyPrice(0.0) {}

    void buy(double price, const std::string& date) {
        int quantity = static_cast<int>(cash / price); // max whole shares affordable
        if (quantity <= 0) return; // not enough cash to buy even 1 share

        cash -= quantity * price;
        sharesHeld = quantity;
        buyPrice = price;

        trades.push_back({"BUY", date, price, quantity});
        std::cout << "  >> BUY: " << quantity << " shares @ $" << price
                  << " on " << date << " | Cash left: $" << cash << "\n";
    }

    void sell(double price, const std::string& date) {
        if (sharesHeld <= 0) return; // nothing to sell

        cash += sharesHeld * price;
        double profit = (price - buyPrice) * sharesHeld;

        trades.push_back({"SELL", date, price, sharesHeld});
        std::cout << "  >> SELL: " << sharesHeld << " shares @ $" << price
                  << " on " << date << " | P/L: $" << profit
                  << " | Cash now: $" << cash << "\n";

        sharesHeld = 0;
        buyPrice = 0.0;
    }

    bool isHolding() const {
        return sharesHeld > 0;
    }

    double getBuyPrice() const {
        return buyPrice;
    }

    void printSummary(double finalPrice) const {
        double totalValue = cash + (sharesHeld * finalPrice);
        std::cout << "\n===== PORTFOLIO SUMMARY =====\n";
        std::cout << "Final cash: $" << cash << "\n";
        std::cout << "Shares still held: " << sharesHeld << "\n";
        std::cout << "Total portfolio value: $" << totalValue << "\n";
        std::cout << "Total trades made: " << trades.size() << "\n";
    }

private:
    double cash;
    int sharesHeld;
    double buyPrice;
    std::vector<Trade> trades;
};