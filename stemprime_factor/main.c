#include "primes.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long long max = 0b10000000000000000;
    if (argc > 1) {
        max = strtoll(argv[1], NULL, 10);
    }
    set_bitarray(max);
}
