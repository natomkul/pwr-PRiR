#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <condition_variable>

class Book
{
 protected:
    const char *bName;

 public:
    Book(const char *bookName);

    const char* get_title() const;
};
