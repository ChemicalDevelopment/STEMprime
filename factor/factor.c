#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <gmp.h>

//Test 2^exponent-1
int test_num(mpz_t prime_cand, int64_t *to_div) {
    int64_t j, k = 0;
    mpz_t cur;
    mpz_init(cur);
    mpz_set(cur, prime_cand);
    for(j = 2; j < sizeof(to_div) * 8; ++j) {
        if ((to_div[j / 64] >> (j % 64)) & 1 == 1) {
            while (mpz_tdiv_ui(cur, (long long)j) == 0) {
                mpz_divexact_ui(cur, cur, (long long)j);
                printf("%lld*", (long long)j);
                ++k;
            }
        }
    }
    if (mpz_sizeinbase(cur, 10) < 80) {
        gmp_printf("%Zd", cur);
    }
    mpz_clear(cur);
    return k;
}
