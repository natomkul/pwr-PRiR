#include "anealling.h"

Anealling::Anealling(std::vector<std::shared_ptr<Node>> current, double temperature) : current(current),
                                                                   temperature(temperature)
{
    count = 0;
    this->size = current.size();

    for (int i = this->size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::swap(this->current[i], this->current[j]);
    }

    Lcurrent = pathL(this->current);

    best = this->current;
    Lbest = Lcurrent;
}

double Anealling::pathL(const std::vector<std::shared_ptr<Node>>& nodes)
{
    double len = 0;

    for (int i = 0; i < (this->size - 1); i++)
    {
        len += sqrt(pow(nodes[i]->X - nodes[i + 1]->X, 2) + pow(nodes[i]->Y - nodes[i + 1]->Y, 2));
    }

    len+= sqrt(pow(nodes[this->size - 1]->X - nodes[0]->X, 2) + pow(nodes[this->size - 1]->Y - nodes[0]->Y, 2));

    return len;
}

std::vector<std::shared_ptr<Node>> Anealling::try_new()
{
    for (int e = 0; e < this->size; e++)
    {
        auto newPath = current;

        int i = rand() % this->size;
        int j;

        do {

            j = rand() % this->size;

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
