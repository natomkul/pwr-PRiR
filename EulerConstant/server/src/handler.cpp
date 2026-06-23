#include "handler.h"

CountHandler::CountHandler(const int n, const int numTh) : n(n), numTh(numTh)
{
    int base = n / numTh;
    int rest = n % numTh;

    int start = 1;
    

    for (int i = 0; i < numTh; i++)
    {
        int size = base + (i < rest ? 1 : 0);
        int end = start + size - 1;

        printf("-------------\nstart: %d\nend:   %d\n", start, end);

        threads.push_back(std::make_unique<Counter>(start, end));

        start = end + 1;
    }

    printf("------------------\n");
    
    for (auto& t : threads)
    {
        printf("thread: %f\n", t->result());
        total += t->result();
    }

    printf("---------------------------\nsum without log: %f\n", total);
}

double CountHandler::finResult()
{
    return total - log(n);
}
