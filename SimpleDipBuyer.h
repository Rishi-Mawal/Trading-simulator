#pragma once
#include "IStrategy.h"
#include "Portfolio.h"
#include <iostream>
#include <string>

class SimpleDipBuyer : public IStrategy {
public:
    SimpleDipBuyer(Portfolio& portfolio) : portfolio(portfolio) {}

    void onBar(const Bar& bar) override {
        std::string dateStr = std::to_string(bar.month) + "/" +
                               std::to_string(bar.day) + "/" +
                               std::to_string(bar.year);

        double dropFromOpen = ((bar.close - bar.open) / bar.open) * 100.0;

        if (!portfolio.isHolding()) {
            if (dropFromOpen <= -5.0) {
                portfolio.buy(bar.close, dateStr);
            }
        } else {
            double changeFromBuy = ((bar.close - portfolio.getBuyPrice()) / portfolio.getBuyPrice()) * 100.0;

            if (changeFromBuy >= 5.0 || changeFromBuy <= -5.0) {
                portfolio.sell(bar.close, dateStr);
            }
        }
    }

private:
    Portfolio& portfolio;
};