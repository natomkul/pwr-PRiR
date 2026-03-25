#include "wrapper.h"

Wrapper::Wrapper(Book *bn) : bn(bn) {}

bool Wrapper::read(int id)
{
    bool ret = this->read_(id);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    return ret;
}

bool Wrapper::read_(int id)
{
    {
        std::unique_lock<std::mutex> lck(mtx_c);
        cv.wait(lck, [&] { return !writing;  });
    }

    {
        std::shared_lock lck_s(mtx_s);
        
        FILE *f = fopen(bn->get_title(), "r");

        if (!f)
        {
            perror("Couldnt open file");
        }
        else {
            char buff[10];

            while (fgets(buff, sizeof(buff), f) != NULL) {
                printf("Reader %d: %s: %s", id, bn->get_title(), buff);
            }


            fclose(f);
        }
    }

    {
        std::unique_lock<std::mutex> lck(mtx_c);
        count++;
    }

    cv.notify_all();

    return true;
}

bool Wrapper::write_(int id)
{
    {
        std::unique_lock<std::mutex> lck(mtx_c);

        cv.wait(lck, [&] { return count > 2 && writing == false; });
        writing = true;
    }

    {
        std::unique_lock lck_s(mtx_s);

        FILE *f = fopen(bn->get_title(), "w+");

        if (!f)
        {
            perror("Couldnt open file");
        }

        int buff = rand() % 1000;

        fprintf(f, "%d \n", buff);

        printf("\nWriter %d: %s: %d \n", id, bn->get_title(), buff);

        fclose(f);
    }

    {
        std::unique_lock<std::mutex> lck(mtx_c);
        count = 0;
        writing = false;
    }

    cv.notify_all();
    return true;
}

bool Wrapper::write(int id)
{
    bool ret = this->write_(id);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    return ret;
}



