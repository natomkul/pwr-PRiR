#include "smoker.h"

Smoker::Smoker(int id, Logger *logg, Matches *matches, Tamper *tampers) 
                 : id_s(id), logg(logg), matches(matches), tampers(tampers)
{
    smk = std::thread(&Smoker::process, this, matches, tampers);
}

Smoker::~Smoker()
{
    if (smk.joinable())
    {
        smk.join();
    }
}

void Smoker::packing()
{
    while (true)
    {
        logg->display(id_s, 3, "trying pack");
        std::this_thread::sleep_for(TIME_WAIT);

        if (tampers->aquireT())
        {
            logg->display(id_s, 2, "packing");
            std::this_thread::sleep_for(TIME_WAIT);
            tampers->relaseT(); 
            break;
        }
    }
}

void Smoker::lighting()
{
    while (true)
    {
        logg->display(id_s, 1, "getting matches");
        std::this_thread::sleep_for(TIME_WAIT);
    
        if (matches->aquireM())
        {
            logg->display(id_s, 4,"lighting");
            std::this_thread::sleep_for(TIME_WAIT);
            matches->relaseM();
            break;
        }
    }
}

void Smoker::smoking()
{
    logg->display(id_s, 0,"smoking");
    std::this_thread::sleep_for(TIME_WAIT);
    return;
}

bool Smoker::process(Matches *matches, Tamper *tampers)
{
    while (true)
    {
        packing();
        lighting();
        smoking();
    }
}

