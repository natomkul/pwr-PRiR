#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include "chopstick.h"

#pragma once

class philosopher
{
private:
     int id_p;

     chopstick* high;
     chopstick* low;

     std::thread phi;

public:
     philosopher(int id, chopstick* h, chopstick* l);
     ~philosopher();
     void hungry();
     void eating();
     void thinks();
     void proc();
     int get_id();
};
