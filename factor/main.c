#include "primes.h"
#include "factor.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

/*
STEMprime factor program.
© ChemicalDevelopment
Project: github.chemicaldevelopment/stemprime

*/

int main(int argc, char *argv[]) {
    long long max = 1000000;
    if (argc > 1) {
        max = strtoll(argv[1], NULL, 10);
    }
    unsigned int * primes;
    set_prime_array(max, &primes);
    printf("Finished prime array\n");
    unsigned int i, j;
    mpz_t n;
    mpz_init(n);
    for (i = (10000000)/2; i < (10000000 + 1000000)/2; ++i) {
        if (get_index(i, primes)) {
            mpz_ui_pow_ui(n, 2, 2 * i + 1);
            mpz_sub_ui(n, n, 1);
            printf("2^%d-1 factors: ", 2 * i + 1);
            j = test_num(n, primes);
            if (j == 0) {
                printf("\r");
            } else {
                printf("\n");
            }
        }
    }
    printf("\n");
}

