#include "primes.h"
#include "mersenne_factor.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, char *argv[]) {
    long long max = 1000;
    if (argc > 1) {
        max = strtoll(argv[1], NULL, 10);
    }
    unsigned int * primes;
    set_prime_array(max, &primes);
    mpz_t n;
    mpz_init(n);
    mpz_ui_pow_ui(n, 2, 3251);
    mpz_sub_ui(n, n, 1);
    test_num(n, primes);
}
