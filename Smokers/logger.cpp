#include "logger.h"

Logger::Logger()
{
    log.release();
}

void Logger::display(int num, int work, const char* mess)
{
    log.acquire();

    switch (work)
    {
        case 0: printf("\033[31mSmoker %d: %s\033[0m\n", num, mess); break;
        case 1: printf("\033[32mSmoker %d: %s\033[0m\n", num, mess); break;
        case 2: printf("\033[33mSmoker %d: %s\033[0m\n", num, mess); break;
        case 3: printf("\033[34mSmoker %d: %s\033[0m\n", num, mess); break;
        case 4: printf("\033[35mSmoker %d: %s\033[0m\n", num, mess); break;
    }

    log.release();
}

