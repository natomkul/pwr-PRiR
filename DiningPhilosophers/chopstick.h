#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#pragma once

class chopstick
{
private:
     std::mutex chop;
     int id_c;

public:
     chopstick(int id);
     virtual void block();
     virtual void relase();
     int get_id();
};

