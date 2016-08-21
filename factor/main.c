#include "factor.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>

/*
STEMprime factor program.
© ChemicalDevelopment
Project: github.chemicaldevelopment/stemprime

*/

int main(int argc, char *argv[]) {
    int64_t min = 10000;
    int64_t max = 12000;
    int64_t max_test = 1000000;
    if (argc > 1) min = strtoll(argv[1], NULL, 10);
    if (argc > 2) max = strtoll(argv[2], NULL, 10); 
    if (argc > 3) max_test = strtoll(argv[3], NULL, 10);
    if (max_test < max) max_test = max; 
    int64_t * to_div = (int64_t *)malloc(sizeof(int64_t) * (max_test / 64) + 1);
    int64_t i;
    mpz_t n;
    mpz_init(n);
    for (i = 3; i < max_test; ++i) {
        mpz_set_ui(n, i);
        if (mpz_probab_prime_p(n, 10)) {
            to_div[i / 64] |= 1 << (i % 64);
        }
    }
    for (i = 32; i < max; ++i) {
        if (to_div[i / 64] >> (i % 64) & 1 == 1) {
            mpz_ui_pow_ui(n, 2, i);
            mpz_sub_ui(n, n, 1);
            printf("M_%lld : ", (long long) i);
            test_num(n, to_div);
            printf("\n");
        }
    }
}

