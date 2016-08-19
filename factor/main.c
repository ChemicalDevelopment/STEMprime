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
    int64_t max = 1000000;
    int64_t start_exp = 10000;
    int64_t end_exp = 11000;
    if (argc > 1) start_exp = strtoll(argv[1], NULL, 10);
    if (argc > 2) end_exp = strtoll(argv[2], NULL, 10);
    if (argc > 3) max = strtoll(argv[3], NULL, 10);
    int64_t * to_div = (int64_t *)malloc(sizeof(int64_t) * (max / 64) + 1);
    int64_t i;
    for (i = 3; i < max; ++i) {
        if (i % 2 == 1) {
            to_div[i / 64] |= 1 << (i % 64);
        }
    }
    mpz_t n;
    mpz_init(n);
    for (i = 2; i < max; ++i) {
        mpz_set_ui(n, i);
        printf("%lld : ", (long long) i);
        test_num(n, to_div);
        printf("\n");
    }
}

