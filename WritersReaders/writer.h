#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include "wrapper.h"

class Writer
{
 private:
    std::thread wr;
    int id;
    void run(std::vector<std::shared_ptr<Wrapper>> bw);
 public:
    Writer(int id, std::vector<std::shared_ptr<Wrapper>> bw);
    ~Writer();
};
