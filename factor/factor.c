#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <gmp.h>

#include "array_management.h"

//Test 2^exponent-1
int test_num(mpz_t prime_cand, unsigned int * primes) {
    unsigned int j, k = 0, rem = 0;
    mpz_t cur;
    mpz_init(cur);
    mpz_set(cur, prime_cand);
    for(j = 0; j < sizeof(primes) * 8; ++j) {
        if (get_index(j, primes)) {
            rem = 0;
            while (rem == 0) {
                rem = mpz_tdiv_ui(cur, 2 * j + 1);
                if (rem == 0) {
                    mpz_divexact_ui(cur, cur, 2 * j + 1);
                    printf("%d*", 2 * j + 1);
                    ++k;
                }
            }
        }
    }
    //gmp_printf("%Zd\n", cur);
    //printf("\n");
    mpz_clear(cur);
    return k;
}
