#include "anealling.h"

Anealling::Anealling(std::vector<std::shared_ptr<Node>> current, double temperature) : current(current), 
                                                                   temperature(temperature)
{
    count = 0;

    Lcurrent = pathL(current);

    best = current;
    Lbest = Lcurrent;
}

double Anealling::pathL(const std::vector<std::shared_ptr<Node>>& nodes)
{
    double len = 0;

    for (int i = 0; i < (nodes_size - 1); i++)
    {
        len += sqrt(pow(nodes[i]->X - nodes[i + 1]->X, 2) + pow(nodes[i]->Y - nodes[i + 1]->Y, 2));
    }

    len+= sqrt(pow(nodes[nodes_size - 1]->X - nodes[0]->X, 2) + pow(nodes[nodes_size - 1]->Y - nodes[0]->Y, 2));

    return len;
}

std::vector<std::shared_ptr<Node>> Anealling::try_new()
{
    auto newPath = current;

    int i = rand() % nodes_size;
    int j;

    do {
    
        j = rand() % nodes_size;

    } while (j == i);

    std::swap(newPath[i], newPath[j]);

    double Lnew = pathL(newPath);

    if (Lnew < Lbest)
    {
        best = newPath;
        Lbest = Lnew;

        current = newPath;
        Lcurrent = Lnew;

    } else if (Lnew < Lcurrent) {

        current = newPath;
        Lcurrent = Lnew;
        
    } else {

        double diff = Lnew - Lcurrent;
        double prob = exp(-(diff) / temperature);
        double randV = (double)rand() / RAND_MAX;

        if (randV < prob)
        {
            current = newPath;
            Lcurrent = Lnew;
        }
    }
        
    temperature *= 0.999;

    if (temperature <= 0.001) 
    {
        count++;
    }

    return current;
}

double Anealling::get_temp()
{
    return temperature;
}

double Anealling::get_len()
{
    return Lcurrent;
}

bool Anealling::get_ended()
{
    if (count > 1000)
    {
        return true; 
    
    } else {
        
        return false;
    }
}
