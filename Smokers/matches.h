#include <iostream>
#include <semaphore>

class Matches
{
 private:
    int m;
    std::counting_semaphore<10> smphM{m};
 public:
    Matches(int m);
    bool aquireM();
    void relaseM();
};

