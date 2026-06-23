#pragma once

#include "counter.h"
#include <vector>

class CountHandler
{
 private:
    const int n;
    const int numTh;

    double total = 0;
    std::vector<std::unique_ptr<Counter>> threads;
 public:
    CountHandler(const int n, const int numThr);
    double finResult();
};
