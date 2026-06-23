#pragma once

#include <iostream>
#include <cmath>
#include <thread>
#include <atomic>

class Counter
{
 private:
    const int n;
    const int start;

    double sum = 0;

    std::thread th;
    std::atomic<bool> ready{false};
 public:
    Counter(const int start, const int n);
    ~Counter();
    void count();
    double result();
};
