#pragma once
#include "DataLoader.h"

class IStrategy {
public:
    virtual ~IStrategy() {}
    virtual void onBar(const Bar& bar) = 0;
};