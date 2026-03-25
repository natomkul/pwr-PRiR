#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <cstdlib>
#include <array>
#include "book.h"
#include "wrapper.h"
#include "reader.h"
#include "writer.h"


int main()
{
    srand(time(NULL));
    Book *bn = new Book("test.txt");
    Wrapper *wp = new Wrapper(bn);
    

    std::vector<std::shared_ptr<Wrapper>> wrappers
    {
        std::make_shared<Wrapper>(new Book("test.txt")),
        std::make_shared<Wrapper>(new Book("test1.txt")),
        std::make_shared<Wrapper>(new Book("test2.txt")),
        std::make_shared<Wrapper>(new Book("test3.txt"))
    };

    const int ri = 5;
    const int wi = 2;

    std::array<std::unique_ptr<Reader>, ri> readers;
    std::array<std::unique_ptr<Writer>, wi> writers;

    for (int i = 0; i < wi; i++)
    {
        writers[i] = std::make_unique<Writer>(i, wrappers);
    }

    for (int i = 0; i < ri; i++)
    {
        readers[i] = std::make_unique<Reader>(i, wrappers);
    }

}
