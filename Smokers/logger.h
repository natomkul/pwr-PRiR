#include <iostream>
#include <semaphore>

class Logger
{
 private:
    std::binary_semaphore log{0};
 public:
    Logger();
    void display(int num, int work, const char* mess);
};
