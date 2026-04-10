#include "smoker.h"

int main()
{
    int m = 4;
    int l = 3;
    int k = 8;

    Matches *mat = new Matches(m);
    Tamper *tam = new Tamper(l);
    Logger *lo = new Logger();

    std::vector<std::unique_ptr<Smoker>> smokers;

    for (int i = 0; i < k; i++)
    {
        smokers.push_back(std::make_unique<Smoker>(i, lo, mat, tam));
    }
}

