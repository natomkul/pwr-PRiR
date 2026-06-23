#include "visual.h"

int main()
{
    int choice;
    const char* fname = nullptr;

    while (fname == nullptr)
    {
        printf("1. kroA100\n2. kroB100\n3. kroC100\n4. kroD100\n5. kroE100\nWybor: ");
        std::cin >> choice;

        switch (choice)
        {
            case 1: fname = "../TSPdata/kroA100.tsp"; break;
            case 2: fname = "../TSPdata/kroB100.tsp"; break;
            case 3: fname = "../TSPdata/kroC100.tsp"; break;
            case 4: fname = "../TSPdata/kroD100.tsp"; break;
            case 5: fname = "../TSPdata/kroE100.tsp"; break;
        }
    }

    wind(100000, fname, "../img/result.png");
}
