#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include "wrapper.h"

class Reader
{
 private:
    std::thread rd;
    int id;
    void run(std::vector<std::shared_ptr<Wrapper>> bw);
 public:
    Reader(int id, std::vector<std::shared_ptr<Wrapper>> bw);
    ~Reader();
};
