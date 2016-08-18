#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <gmp.h>

#include "array_management.h"

//Test 2^exponent-1
unsigned int test_num(mpz_t prime_cand, unsigned int * primes) {
    int j;
    for(j = 0; j < 2; ++j) {
        if (get_index(j, primes)) {
            if (mpz_gcd_ui(NULL, prime_cand, 2 * j + 3) != 1) {
                return 0;
            }
        }
    }
    return 1;
}
