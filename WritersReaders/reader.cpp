#include "reader.h"
#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include "wrapper.h"

Reader::Reader(int id, std::vector<std::shared_ptr<Wrapper>> bw) : id(id)
{
    rd = std::thread(&Reader::run, this, bw);
}

Reader::~Reader()
{
    if (rd.joinable())
    {
        rd.join();
    }
}

void Reader::run(std::vector<std::shared_ptr<Wrapper>> bw)
{
    while(true)
    {
        int idx = rand() % bw.size();

        if (!bw[idx]->read(id))
            return;
    }
}
