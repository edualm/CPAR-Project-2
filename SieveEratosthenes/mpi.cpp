//
//  main.cpp
//  SieveEratosthenes
//
//  Created by Eduardo Almeida on 16/05/16.
//  Copyright © 2016 Eduardo Almeida. All rights reserved.
//

#include <iostream>

#include <cmath>
#include <ctime>
#include <cstring>
#include "mpi.h"

void printUnmarked(long long upperBound, bool *marked) {
    for (long long i = 0; i <= upperBound; i++)
        if (!marked[i])
            std::cout << i << " ";
}

void runEratosthenesSieve(long long upperBound, int numThreads, bool print) {
    int upperBoundSquareRoot = (int)sqrt(upperBound), size = upperBound + 1, rank = 0, numtasks = 0;
    bool *marked = new bool[size];
    bool *recvbuf = new bool[size/4];

     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    memset(marked, 0, sizeof(bool) * (size));

    for (long long m = 2; m <= upperBoundSquareRoot; m++) {
        MPI_Bcast(&m, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        if (!marked[m])
        MPI_Scatter(marked, size, MPI_C_BOOL, recvbuf, size/4, MPI_C_BOOL, 0, MPI_COMM_WORLD);
            for (long long k = (rank*upperBound/4 + 2) * m; k <= upperBound/4*(rank + 1); k += m)
                recvbuf[k+(rank*size/4)] = true;
                //marked[k] = true;
    }
    MPI_Gather(&recvbuf, size/4, MPI_C_BOOL, marked, size, MPI_C_BOOL, 0, MPI_COMM_WORLD);

    if (print)
        printUnmarked(upperBound, marked);

    delete [] marked;
}

int main(int argc, char * argv[]) {
    MPI_Init(&argc,&argv);

    runEratosthenesSieve(pow(2, 30), 4, false);

    return 0;
}
