#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include "writer.h"
#include "wrapper.h"

Writer::Writer(int id, std::vector<std::shared_ptr<Wrapper>> bw) : id(id)
{
    wr = std::thread(&Writer::run, this, bw);
}

Writer::~Writer()
{
    if (wr.joinable())
    {
        wr.join();
    }
}

void Writer::run(std::vector<std::shared_ptr<Wrapper>> bw)
{
    while(true)
    {
        int idx = rand() % bw.size();

        if (!bw[idx]->write(id))
            return;

    }
}
