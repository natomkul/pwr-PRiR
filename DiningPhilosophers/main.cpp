#include "chopstick.h"
#include "philosopher.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <deque>
#include <memory>
#include <condition_variable>

void feast(int n)
{
    std::deque<chopstick> chopsticks;

    for (int i = 0; i < n; i++)
    {
        chopsticks.emplace_back(i);
    }

    std::deque<philosopher> philosophers;

    int a;
    int b;

    for (int i = 0; i < n; i++)
    {
         a = i;
         b = (i + 1) % n;
        if (a > b)
        {
            chopstick* primo = &chopsticks[a];
            chopstick* sec = &chopsticks[b];

            philosophers.emplace_back(i, primo, sec);
        } else {
            chopstick* primo = &chopsticks[b];
            chopstick* sec = &chopsticks[a];

            philosophers.emplace_back(i, primo, sec);
        }
    }
}


int main() 
{
    feast(5);
    return 0;
}
