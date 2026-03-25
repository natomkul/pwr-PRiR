#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <cstdlib>

#include "book.h"

class Wrapper
{
 private:
    Book *bn;
    int count = 3;
    bool writing = false;

    std::mutex mtx_c; //mutex for control over count & writing
    std::shared_mutex mtx_s; // mutex for actions
    std::condition_variable cv;

    bool read_(int id);
    bool write_(int id);

 public:
    Wrapper(Book *bn);

    bool read(int id);
    bool write(int id);

    auto get_bn_name() const
    {
         return bn->get_title();
    }
};
