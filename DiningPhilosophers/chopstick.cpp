#include "chopstick.h"
#include <iostream>                                                     
#include <thread>
#include <mutex>
#include <chrono>

chopstick::chopstick(int id) : id_c(id) {}

void chopstick::block()
{
    chop.lock();
}

void chopstick::relase()
{
    chop.unlock();
}

int chopstick::get_id()
{
    return id_c;
}
