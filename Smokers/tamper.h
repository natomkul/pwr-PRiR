#include <iostream>
#include <semaphore>

class Tamper
{
 private:
    int l;
    std::counting_semaphore<10> smphT{l};
 public:
    Tamper(int l);
    bool aquireT();
    void relaseT();
};

