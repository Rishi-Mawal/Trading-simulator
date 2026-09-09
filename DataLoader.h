#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct Bar {
    int month, day, year;
    double open;
    double high;
    double low;
    double close;
    long long volume;
};

std::vector<Bar> loadData(const std::string& filepath) {
    std::vector<Bar> bars;
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file!\n";
    }
    std::string line;

    // should skip header row now
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string dateStr, openStr, highStr, lowStr, closeStr, volumeStr;

        std::getline(ss, dateStr, ',');
        std::getline(ss, openStr, ',');
        std::getline(ss, highStr, ',');
        std::getline(ss, lowStr, ',');
        std::getline(ss, closeStr, ',');
        std::getline(ss, volumeStr, ',');

        Bar bar;
        sscanf(dateStr.c_str(), "%d/%d/%d", &bar.month, &bar.day, &bar.year);

        bar.open = std::stod(openStr);
        bar.high = std::stod(highStr);
        bar.low = std::stod(lowStr);
        bar.close = std::stod(closeStr);
        bar.volume = std::stoll(volumeStr);

        bars.push_back(bar);
    }

    return bars;
}   

std::vector<Bar> getRecentBars(const std::vector<Bar>& allBars, int count) {
    if (allBars.size() <= count) {
        return allBars;
    }
    return std::vector<Bar>(allBars.end() - count, allBars.end());
}
