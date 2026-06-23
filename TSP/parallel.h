#pragma once

#include <mpi.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "opener.h"
#include "anealling.h"

void parall(int argc, char** argv, double temp, const char* fname)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);

    Data* proc = new Data(fname);

    double start = MPI_Wtime();

    Anealling* prob = new Anealling(proc->get_nodes(), temp);

    while (!prob->get_ended())
    {
        prob->try_new();
    }

    double elapsed = MPI_Wtime() - start;
    double len = prob->get_len();

    double bestLen;
    MPI_Reduce(&len, &bestLen, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

    double maxTime;
    MPI_Reduce(&elapsed, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        std::cout << "procesy: " << size << "  najlepsza dlugosc: " << bestLen << "  czas: " << maxTime << "s\n";
    }

    delete proc;
    delete prob;

    MPI_Finalize();
}
