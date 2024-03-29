//
//  SieveEratosthenes
//  OpenMP Version
//
//  Based on http://www.algolist.net/Algorithms/Number_theoretic/Sieve_of_Eratosthenes
//

#include <iostream>

#include <cmath>
#include <ctime>
#include <cstring>

#include <omp.h>

void printUnmarked(long long upperBound, bool *marked) {
    for (long long i = 0; i <= upperBound; i++)
        if (!marked[i])
            std::cout << i << " ";
}

void runEratosthenesSieve(long long upperBound, int numThreads, bool print) {
    double time1, time2;
    
    int upperBoundSquareRoot = (int)sqrt(upperBound);
    bool *marked = new bool[upperBound + 1];
    
    memset(marked, 0, sizeof(bool) * (upperBound + 1));
    
    time1 = omp_get_wtime();
    
    for (long long m = 2; m <= upperBoundSquareRoot && !marked[m]; m++)
#pragma omp parallel for num_threads(numThreads)
        for (long long k = m * m; k <= upperBound; k += m)
            marked[k] = true;
    
    time2 = omp_get_wtime();
    
    if (print)
        printUnmarked(upperBound, marked);
    
    std::cout << "Upper bound: " << upperBound << " - Time: " << time2 - time1 << " - Threads: " << numThreads << std::endl;
    
    delete [] marked;
}

int main(int argc, const char * argv[]) {
    for (int i = 25; i <= 32; i++)
        for (int j = 1; j <= 4; j++)
            runEratosthenesSieve(pow(2, i), j, false);
    
    return 0;
}