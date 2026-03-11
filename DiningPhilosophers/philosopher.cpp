#include "chopstick.h"
#include "philosopher.h"
#include <iostream>                                                     
#include <thread>
#include <mutex>
#include <chrono>

philosopher::philosopher(int id, chopstick* h, chopstick* l) 
    : id_p(id), high(h), low(l)
{
   phi = std::thread(&philosopher::proc, this);
}

philosopher::~philosopher() 
{
    if (phi.joinable()) 
    {
        phi.join();
    }
}

void philosopher::hungry()
{
    printf("%d: Philosopher is HUNGRY\n", get_id());

    std::this_thread::sleep_for(std::chrono::seconds(3));

    low->block();
    high->block();
}

void philosopher::eating()
{
    printf("%d: Philosopher is EATING\n", get_id());

    std::this_thread::sleep_for(std::chrono::seconds(3));

    high->relase();
    low->relase();
}

void philosopher::thinks()
{
    printf("%d: Philosopher is THINKING\n", get_id());

    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void philosopher::proc()
{
    while (true)
    {
        thinks();
        hungry();
        eating();
    }
}

int philosopher::get_id() { return id_p; }

