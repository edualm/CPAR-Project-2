+//
 +//  main.cpp
 +//  SieveEratosthenes
 +//
 +//  Created by Eduardo Almeida on 16/05/16.
 +//  Copyright © 2016 Eduardo Almeida. All rights reserved.
 +//
 +
 +#include <iostream>
 +
 +#include <cmath>
 +#include <ctime>
 +#include <cstring>
 +
 +void printUnmarked(long long upperBound, bool *marked) {
 +    for (long long i = 0; i <= upperBound; i++)
 +        if (!marked[i])
 +            std::cout << i << " ";
 +}
 +
 +void runEratosthenesSieve(long long upperBound, int numThreads, bool print) {
 +    int upperBoundSquareRoot = (int)sqrt(upperBound);
 +    bool *marked = new bool[upperBound + 1];
 +    
 +    memset(marked, 0, sizeof(bool) * (upperBound + 1));
 +    
 +    for (long long m = 2; m <= upperBoundSquareRoot; m++)
 +        if (!marked[m])
 +            for (long long k = m * m; k <= upperBound; k += m)
 +                marked[k] = true;
 +    
 +    if (print)
 +        printUnmarked(upperBound, marked);
 +    
 +    delete [] marked;
 +}
 +
 +int main(int argc, const char * argv[]) {

 +    runEratosthenesSieve(pow(2, 30), 4, false);
 +
 +    return 0;
 +}