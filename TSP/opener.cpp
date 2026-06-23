#include "opener.h"
#include <cstring>

Data::Data(const char* file)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("Blad otwarcia pliku\n");
        exit(1);
    }

    char token[256];

    while (fscanf(fp, "%255s", token) == 1)
    {
        if (strcmp(token, "DIMENSION:") == 0)
        {
            fscanf(fp, "%d", &this->size);

        } else if (strcmp(token, "NODE_COORD_SECTION") == 0) {

            break;
        }
    }

    for (int i = 0; i < this->size; i++)
    {
        Node temp{};
        fscanf(fp, "%d %d %d", &temp.id, &temp.X, &temp.Y);

        min_x = std::min(temp.X, min_x);
        min_y = std::min(temp.Y, min_y);

        max_x = std::max(temp.X, max_x);
        max_y = std::max(temp.Y, max_y);

        nodes.emplace_back(std::make_shared<Node>(temp));
    }

    fclose(fp);
}

void Data::printData()
{
    for (int i = 0; i < this->size; i++)
    {
        printf("indx: %d  ", i);
        printf("id: %d  ", nodes[i]->id);
        printf("X: %d  ", nodes[i]->X);
        printf("Y: %d\n", nodes[i]->Y);
    }
}

int Data::get_minX()
{
    return min_x;
}

int Data::get_maxX()
{
    return max_x;
}

int Data::get_minY()
{
    return min_y;
}

int Data::get_maxY()
{
    return max_y;
}

int Data::get_size()
{
    return this->size;
}

std::vector<std::shared_ptr<Node>> Data::get_nodes()
{
    return nodes;
}

